<?php

/**
 * Description of invoiceUpload
 *
 */
class invoiceUpload extends FeedsProcessor {

    /**
     * 
     * Dummy override. Does nothing.
     */
    protected function entityDeleteMultiple($entity_ids) {
        
    }

    protected function entitySave($entity) {
        
    }

    protected function newEntity(FeedsSource $source) {
        
    }

    protected function entityLoad(FeedsSource $source, $entity_id) {
        
    }

    /**
     * Entity type this processor (supposedly) operates on. Not used in actual processing.
     */
    public function entityType() {
        return 'user';
    }

    /**
     * Process the result of the parsing stage.
     *
     * @param FeedsSource $source
     *   Source information about this import.
     * @param FeedsParserResult $parser_result
     *   The result of the parsing stage.
     */
    public function process(FeedsSource $source, FeedsParserResult $parser_result) {

        $cached = cache_get('invoice_importer_status_progress');
        $errors = array();
        $row = 0;
        if (is_object($cached)) {
            $data = $cached->data;
            $errors = $data['errors'];
            $row = $data['row'];
        }
        $col_map = array();
        foreach ($this->config['mappings'] as $mapping) {
            $col_map[($mapping['source'])] = $mapping['target'];
        }
        $table_cust_inv = db_select('c_form_pendency', 'c')->fields('c', array('cust_inv', 'cust_inv'))->execute()->fetchAllKeyed();
        // $table_tin = db_select('c_form_pendency', 'd')->fields('d', array('invoice_number', 'invoice_number'))->execute()->fetchAllKeyed();
        // $table_tin = db_select('c_form_pendency', 'd')->fields('d', array('tin_number', 'tin_number'))->execute()->fetchAllKeyed();
        $mapping = $this->getMappingTargets();
        while ($item = $parser_result->shiftItem()) {
            $transaction = db_transaction();
            $row++;
            $error = FALSE;
            $data = array();
            //if (!empty($item['INVOICE NUMBER']) && !empty($item['TIN NUMBER'])) {
            if (!empty($item['CONCATENATE'])) {
                foreach ($item as $key => $lvalue) {
                    $value = trim($lvalue);
                    $msg = '';

                    if ($value != NULL && $value != '') {
                        if (isset($mapping[$col_map[$key]]['length']) && strlen($value) > $mapping[$col_map[$key]]['length']) {
                            $msg = 'Field ' . $mapping[$col_map[$key]]['name'] . ' must be less than or equal to ' . $mapping[$col_map[$key]]['length'] . ' characters in row ' . $row;
                            $error = TRUE;
                        }
                        if (isset($mapping[$col_map[$key]]['numeric']) && !is_numeric($value)) {
                            $msg = 'Field ' . $mapping[$col_map[$key]]['name'] . ' must be numeric in row ' . $row;
                            $error = TRUE;
                        }
                        if (isset($mapping[$col_map[$key]]['function']) && !call_user_func($mapping[$col_map[$key]]['function'], $value)) {
                            $msg = 'Field ' . $mapping[$col_map[$key]]['name'] . ' value is invalid in row ' . $row;
                            $error = TRUE;
                        }

                        if (isset($mapping[$col_map[$key]]['taxonomy_term']) && !($value = ut_importer_get_tid($value, $mapping[$col_map[$key]]['vocabulary']))) {
                            $msg = 'Field ' . $mapping[$col_map[$key]]['name'] . ' value in row ' . $row . ' not found.';
                            $error = TRUE;
                        }

                        //sample condition for checking the values in the feeds before inserting to table    

                        /* if (($mapping[$col_map[$key]]['name'] == 'invoice number' 
                          && (empty($value)||$value == 0))) {
                          $msg = 'Field value empty';
                          $error = TRUE;
                          drupal_set_message('error test ->' . $msg);
                          }
                         */


//                    if (is_array($value)) {
//                        if (!$error && isset($col_map[$key])) {
//                            //$value = preg_replace('/[^(\x20-\x7F)]*/', '', $lvalue);
//                            $data[$col_map[$key]] = $value;
//                        }
//                    }
//                    else {
//                        if (!$error && isset($col_map[$key])) {
//                            $value = preg_replace('/[^(\x20-\x7F)]*/', '', $value);
//                            $data[$col_map[$key]] = $value;
//                        }
//                    }

                        if (!$error && isset($col_map[$key])) {
                            $value = preg_replace('/[^(\x20-\x7F)]*/', '', $value);
                            if ($col_map[$key] == 'status') {
                                $stat = array_search(strtolower($value), array_map('strtolower', arr_status()));
                                $value = $stat != NULL && !empty($stat) ? $stat : 100;
                            }
                            elseif ($col_map[$key] == 'collectable') {
                                $col = array_search(strtolower($value), array_map('strtolower', arr_collectable()));
                                $value = $col != NULL && !empty($col) ? $col : 1;
                            }
                            if($col_map[$key] == 'agent'){
                                $agent = array_search(strtolower($value), array_map('strtolower', arr_agents()));
                                $value = $agent != NULL && !empty($agent) ? $agent : 1;
                            }
                            $data[$col_map[$key]] = $value;
                        }
                    }
                    elseif ($mapping[$col_map[$key]]['mandatory']) {
                        $msg = 'Field ' . $mapping[$col_map[$key]]['name'] . ' cannot be empty in row ' . $row;
                        $error = TRUE;
                    }
                    elseif (!empty($key) && !isset($col_map[$key])) {

                        $data[$col_map[$key]] = NULL;
                    }

                    if (!empty($msg)) {
                        $errors[] = $msg;
                    }
                }
            }
            else {
                //$errors[] = ('Field invoice number or tin number cannot be empty in row ' . $row);
                $errors[] = ('Field Concatenate cannot be empty in row ' . $row);

                $error = TRUE;
            }
            //rejects the data if the invoice number or tin number is empty as they are primary keys                  
            // if (empty($data['invoice_number']) || empty($data['tin_number'])) {
            // $error = TRUE;
            // dsm('no invoice number or tin number...! data rejected for row ' . $row);
            // }
            //now save the data
            if (!$error) {
                //update if is existing
                /* $table_al = db_select('c_form_pendency', 'c')
                  ->fields('c')
                  ->condition('invoice_number', $data[drupal_strtolower('invoice_number')], '=')
                  ->execute()
                  ->fetchAssoc(); */
                // dpm($table_al);
                $duplicate_id_diff_content = FALSE;

                try {
                    // $original_values = array();
                    // $duplicate_values = array();
                    // dpm('inv:'.$table_inv[$data['invoice_number']]);
                    // dpm('tin:'.$table_tin[$data['tin_number']]);
//                    if (isset($table_inv[$data['invoice_number']]) && isset($table_tin[$data['tin_number']])) {
//                        if (!empty($table_inv[$data['invoice_number']]) && !empty($table_tin[$data['tin_number']])) {
                    if (isset($table_cust_inv[$data['cust_inv']])) {
                        if (!empty($table_cust_inv[$data['cust_inv']])) {
                            /* foreach ($item as $key => $val) {
                              if ($data[drupal_strtolower($key)] != $table_al[drupal_strtolower($key)]) {
                              $duplicate_id_diff_content = TRUE;
                              //dpm('original ' . $key . ' = ' . $table_al[drupal_strtolower($key)] . ' and duplicate ' . $key . ' = ' . $data[drupal_strtolower($key)]);
                              }
                              }
                              if ($duplicate_id_diff_content) {

                              /*
                             * notify user-> ask for reject data or update existing data.
                             */

                            // dsm('duplicate id and different content in row' . $row . 'with invoice no  ' . $table_inv[$data['invoice_number']] . ' ....do you want to update or reject?');
                            db_update('c_form_pendency')
                                ->fields($data)
                                ->condition('cust_inv', $table_cust_inv[$data['cust_inv']], '=')
                                // ->condition('tin_number', $table_tin[$data['tin_number']], '=')
                                ->execute();
                            $errors[] = ('Field concatenate is same in row ' . $row . '. Data updated');
                        }
                        /* else {
                          // dsm('duplicate id and duplicate content in row' . $row . '...data rejected');
                          }
                          } */
                    }
                    else {
                        //else insert
                        //dsm('new data inserted');
                        $iquery = db_insert('c_form_pendency')->fields($data)->execute();
                        $table_cust_inv[$data['cust_inv']] = 0;
                        //$table_tin[$data['tin_number']] = 0;
                    }
                }
                catch (Exception $ex) {
                    $transaction->rollback();
                    watchdog_exception('php', $ex);
                    $errors[] = ('unexpected error in ' . $row);
                    // drupal_set_message($ex);
                }
            }
        }
        //drupal_set_message(l('import complete','ut/edit-page'));

        if ($source->progressImporting() == FEEDS_BATCH_COMPLETE) {
            cache_set('invoice_importer_status', array('errors' => $errors, 'row' => $row));
            cache_clear_all('invoice_importer_status_progress', 'cache');
        }
        else {
            cache_set('invoice_importer_status_progress', array('errors' => $errors, 'row' => $row));
        }
    }

    /**
     * Implements parent::entityInfo().
     */
    protected function entityInfo() {
        $info = parent::entityInfo();
        $info['label plural'] = t('Entries');
        return $info;
    }

    /**
     * Return available mapping targets.
     */
    public function getMappingTargets() {
        return array(
          /*  'sr_no' => array(
            'name' => t('sr no'),
            'description' => t('Serial number'),
            'mandatory' => FALSE,
            'length' => 10,
            ), */

          'cust_inv' => array(
            'name' => t('cust_inv'),
            'description' => t('Combination of cust_code, cust_name and inv_number'),
            'mandatory' => TRUE,
            'length' => 100,
          ),
          'sap_customer_code' => array(
            'name' => t('sap customer code'),
            'description' => t('SAP Customer code'),
            'mandatory' => FALSE,
            'length' => 50,
          ),
          'goods_supplied_from_state' => array(
            'name' => t('goods supplied from_state'),
            'description' => t('Invoice number'),
            'mandatory' => FALSE,
            'length' => 200,
          ),
          /* 'vc_comp_code' => array(
            'name' => t('vc comp code'),
            'description' => t('Customer name'),
            'mandatory' => FALSE,
            'length' => 150,
            ),
            'vc_comp_initial' => array(
            'name' => t('vc comp initial'),
            'description' => t('Customer name'),
            'mandatory' => FALSE,
            'length' => 150,
            ), */
          'invoice_number' => array(
            'name' => t('invoice number'),
            'description' => t('invoice number'),
            'mandatory' => FALSE,
            'length' => 25,
          ),
          'customer_name' => array(
            'name' => t('customer name'),
            'description' => t('customer name'),
            'mandatory' => FALSE,
            'length' => 200,
          ),
          'customer_address' => array(
            'name' => t('customer address'),
            'description' => t('customer address'),
            'mandatory' => FALSE,
            'length' => 255,
          ),
          /*  'customer_location' => array(
            'name' => t('customer location'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 150,
            ), */
          'customer_contact' => array(
            'name' => t('customer contact'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 500,
          ),
          /* 'customer_mobile' => array(
            'name' => t('customer mobile'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 11,
            ), */
          'contact_email' => array(
            'name' => t('contact email'),
            'description' => t('contact email'),
            'mandatory' => FALSE,
            'length' => 500,
          ),
          'quarter' => array(
            'name' => t('quarter'),
            'description' => t('quarter'),
            'mandatory' => FALSE,
            'length' => 30,
          ),
          'finantial_year' => array(
            'name' => t('finantial year'),
            'description' => t('finantial year'),
            'mandatory' => FALSE,
            'length' => 10,
          ),
          'invoice_date' => array(
            'name' => t('invoice date'),
            'description' => t('invoice date'),
            'mandatory' => FALSE,
            'length' => 15,
          ),
          /* 'month' => array(
            'name' => t('month'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 10,
            ), */
          'inv_amt' => array(
            'name' => t('inv amt'),
            'description' => t('inv amt'),
            'mandatory' => FALSE,
            'length' => 100,
          ),
          /* 'currency' => array(
            'name' => t('currency'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 20,
            ), */
          'po_number' => array(
            'name' => t('po number'),
            'description' => t('po number'),
            'mandatory' => FALSE,
            'length' => 100,
          ),
          'tin_number' => array(
            'name' => t('tin number'),
            'description' => t('tin number'),
            'mandatory' => FALSE,
            'length' => 20,
          ),
          'issue_c_form_to_entity_name' => array(
            'name' => t('issue c form to entity name'),
            'description' => t('issue c form to entity name'),
            'mandatory' => FALSE,
            'length' => 100,
          ),
          'form_type' => array(
            'name' => t('form type'),
            'description' => t('form type'),
            'mandatory' => FALSE,
            'length' => 100,
          ),
          'bill_state' => array(
            'name' => t('bill state'),
            'description' => t('bill state'),
            'mandatory' => FALSE,
            'length' => 25,
          ),
          /* 'region' => array(
            'name' => t('region'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 100,
            ), */
          'total_differential_tax_liability' => array(
            'name' => t('total differential tax liability'),
            'description' => t('total differential tax liability'),
            'mandatory' => FALSE,
            'length' => 50,
          ),
          'division_grouping' => array(
            'name' => t('division grouping'),
            'description' => t('Division Grouping'),
            'mandatory' => FALSE,
            'length' => 20,
          ),
          'sub_division' => array(
            'name' => t('sub division'),
            'description' => t('Sub Division'),
            'mandatory' => FALSE,
            'length' => 20,
          ),
          /* 'main_division' => array(
            'name' => t('main division'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 10,
            ),
            'sales_person_code' => array(
            'name' => t('sales person code'),
            'description' => t('Custome contact'),
            'mandatory' => FALSE,
            'length' => 25,
            ),
            'sales_person_name' => array(
            'name' => t('sales person name'),
            'description' => t('Sales persons name'),
            'mandatory' => FALSE,
            'length' => 125,
            ), */
          'status' => array(
            'name' => t('status'),
            'description' => t('collectible status'),
            'mandatory' => FALSE,
            'length' => 25,
          ),
          'collectable' => array(
            'name' => t('collectable'),
            'description' => t('collectible'),
            'mandatory' => FALSE,
            'length' => 25,
          ),
          'lost_case_wrong_issuance' => array(
            'name' => t('Lost case / wrong issuance'),
            'description' => t('Lost case / wrong issuance'),
            'mandatory' => FALSE,
            'length' => 50,
          ),
          'remarks' => array(
            'name' => t('remarks'),
            'description' => t('remarks'),
            'mandatory' => FALSE,
            'length' => 500,
          ),
          'focus_account' => array(
            'name' => t('focus account'),
            'description' => t('focus account'),
            'mandatory' => FALSE,
            'length' => 50,
          ),
          'feedback' => array(
            'name' => t('feedback'),
            'description' => t('feedback'),
            'mandatory' => FALSE,
            'length' => 500,
          ),
          'agent' => array(
            'name' => t('Agent'),
            'description' => t('Agent'),
            'mandatory' => FALSE,
            'length' => 25,
          ),
        );
    }

    /**
     * Counts the number of items imported by this processor.
     */
    public function itemCount(FeedsSource $source) {
        $query = db_select('c_form_pendency', 'c');
        $query->addExpression('count(*)');
        return $query->execute()->fetchField();
    }

}
