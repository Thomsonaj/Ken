<?php

/**
 * Implements hook_views_data().
 */
function main_views_data() {

    $data = array();

    $data['c_form_pendency']['table']['group'] = t('View Invoices');

    $data['c_form_pendency']['table']['base'] = array(
      // 'field' => 'invoice_number',   
      'title' => t('View Invoices'),
      'help' => t('Contains records in c_form_pendency table which is exposed to Views.'),
        // 'weight' => -10,
    );

 $data['c_form_pendency']['table']['join']['ken_promise_dates'] = array(
   'left_field' => 'invoice_nummber',
   //'left_table' => 'invoice_nummber',
   'field' => 'invoice_nummber',
   'type' => 'INNER',
 );

    //adding fields to exposed table..

    $data['c_form_pendency']['sr_no'] = array(
      'title' => t('Serial No'),
      'help' => t('Serial No of invoices.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
    );

    $data['c_form_pendency']['sap_customer_code'] = array(
      'title' => t('SAP Customer Code'),
      'help' => t('sap customer code'),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['goods_supplied_from_state'] = array(
      'title' => t('Goods Supplied From State'),
      'help' => t('Goods supplied from state'),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['vc_comp_code'] = array(
      'title' => t('VC Comp Code'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['vc_comp_initial'] = array(
      'title' => t('VC Comp Initial'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

//invoice number..
    $data['c_form_pendency']['invoice_number'] = array(
      'title' => t('Invoice Number'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
           
    );

    $data['c_form_pendency']['customer_name'] = array(
      'title' => t('Customer Name'),
      'help' => t('Name of the customer'),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_autoload_name',
      ),
    );

    $data['c_form_pendency']['customer_address'] = array(
      'title' => t('Customer Address'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['customer_location'] = array(
      'title' => t('Customer Location'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['customer_contact'] = array(
      'title' => t('Customer Contact'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['customer_mobile'] = array(
      'title' => t('Customer Mobile'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['contact_email'] = array(
      'title' => t('Contact Email'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['quarter'] = array(
      'title' => t('Quarter'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_select_quarter',
      ),
    );

    $data['c_form_pendency']['finantial_year'] = array(
      'title' => t('Financial Year'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_select_finantial_year',
      ),
    );

    $data['c_form_pendency']['invoice_date'] = array(
      'title' => t('Invoice Date'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['month'] = array(
      'title' => t('Month'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['inv_amt'] = array(
      'title' => t('Invoice Amount'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['currency'] = array(
      'title' => t('Currency'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['po_number'] = array(
      'title' => t('PO Number'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['tin_number'] = array(
      'title' => t('Tin Number'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['issue_c_form_to_entity_name'] = array(
      'title' => t('Issue C Form To Entity Name'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['form_type'] = array(
      'title' => t('Form Type'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['bill_state'] = array(
      'title' => t('Bill State'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['region'] = array(
      'title' => t('Region'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['total_differential_tax_liability'] = array(
      'title' => t('Total Differential Tax Liability'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['division'] = array(
      'title' => t('Division'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_select_division',
      ),
    );

    $data['c_form_pendency']['sub_division'] = array(
      'title' => t('Sub Division'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['main_division'] = array(
      'title' => t('Main Division'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_select_main_division',
      ),
    );

    $data['c_form_pendency']['sales_person_code'] = array(
      'title' => t('Sales Persons Code'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['sales_person_name'] = array(
      'title' => t('Sales Persons Name'),
      'help' => t(''),
      'field' => array(
        'handler' => 'views_handler_field',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['c_form_pendency']['status'] = array(
      'title' => t('Status'),
      'help' => t('Status of invoices.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_select_status',
      ),
    );

    $data['c_form_pendency']['collectable'] = array(
      'title' => t('Collectable'),
      'help' => t('Invoices collectable status.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_select_collectable',
      ),
    );

    return $data;
}
