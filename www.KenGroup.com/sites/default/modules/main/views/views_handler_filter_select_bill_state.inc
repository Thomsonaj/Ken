<?php

class views_handler_filter_select_bill_state extends views_handler_filter_boolean_operator {

    function construct() {
        $this->value_value = t('Select bill state');
        parent::construct();
    }
//
    function get_value_options() {
        $view = $_GET['q'];
        if (!empty($view)) {
            if ($view == 'view-invoices') {
                $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                    ->condition('issue_c_form_to_entity_name', 'Thermo Fisher Scientific India Pvt Ltd')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
            }
            elseif ($view == 'view-invoices-dionex') {
//        $or = db_or()
//            ->condition('issue_c_form_to_entity_name','Thermo Fisher Scientific India Pvt Ltd')
//            ->condition('tid2', 6);
                $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                    ->condition('issue_c_form_to_entity_name', 'Thermo Fisher Scientific India Pvt Ltd', '!=')
                    ->condition('issue_c_form_to_entity_name', 'Client 1', '!=')
                    ->condition('issue_c_form_to_entity_name', 'Neela Systems Ltd.', '!=')
                    ->condition('issue_c_form_to_entity_name', 'Praj HiPurity Systems Ltd.', '!=')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
            }
            elseif ($view == 'view-lost-forms') {
                $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                    ->condition('form_type', 'Lost forms')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
            }
            elseif ($view == 'view-client1-invoices') {
                $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                    ->condition('issue_c_form_to_entity_name', 'Client 1')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
            }
            elseif ($view == 'view-praj-invoices') {
                $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                     ->condition('issue_c_form_to_entity_name', 'Thermo Fisher Scientific India Pvt Ltd', '!=')
                    ->condition('issue_c_form_to_entity_name', 'Client 1', '!=')
                     ->condition('issue_c_form_to_entity_name', 'Dionex India Pvt Ltd', '!=')
                    ->condition('issue_c_form_to_entity_name', 'Thermo Electron India Pvt Ltd', '!=')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
            }
            else {
                $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
            }
        }else{
            $states = db_select('c_form_pendency', 'e')
                    ->fields('e', array('bill_state'))//SELECT the fields from node
                    ->distinct()
                    ->condition('bill_state', NULL, 'IS NOT')
                    ->condition('issue_c_form_to_entity_name', 'Thermo Fisher Scientific India Pvt Ltd')
                    ->orderBy('e.bill_state', 'ASC')
                    ->execute();
        }
//        $states = db_select('c_form_pendency', 'e')
//            ->fields('e', array('bill_state'))//SELECT the fields from node
//            ->distinct()
//            ->condition('bill_state', NULL, 'IS NOT')
//            ->orderBy('e.bill_state', 'ASC')
//            ->execute();
        $all_state = array();
        foreach ($states as $state) {
            foreach ($state as $city) {
                if (!empty($city)) {
                    $all_state[$city] = $city;
                }
            }
        }
        $this->value_options = $all_state;
    }

    function value_form(&$form, &$form_state) {
        // Initialize the array of possible values for this filter.
        $this->get_value_options();

        $form['value'] = array(
          '#type' => 'select',
          '#title' => t('Select bill state'),
          '#options' => $this->value_options,
          '#default_value' => '',
        );
    }

    function query() {
        $this->ensure_my_table();
        $where = "$this->table_alias.$this->real_field ";
        if ($this->value != 'all') {
            $operator = '=';
            $this->query->add_where($this->options['group'], $where, $this->value, $operator);
        }
    }

}
