<?php

class views_handler_filter_autoload_name extends views_handler_filter_string {

    function construct() {
        $this->value_value = t('Select Customer Name');
        parent::construct();
    }

    function get_value_options() {

        //$this -> value_options = arr_status();
    }

 /*   function value_menu() {
        $items['kengroup/autocomplete'] = array(
          'page callback' => 'value_autocomplete',
         // 'access arguments' => array('access example autocomplete'),
          'access callback' => 'user_is_logged_in',
          'type' => MENU_CALLBACK
        );

        return $items;
    }*/

    function value_form(&$form, &$form_state) {
        // Initialize the array of possible values for this filter.
        $this->get_value_options();

        $form['value'] = array(
          '#type' => 'textfield',
          '#title' => t('Enter Customer Name'),
          '#size' => 30,
          '#autocomplete_path' => 'kengroup/autocomplete',
          '#default_value' => '',
          '#attributes' => array(
            'onfocus' => "if (this.value = this.value) {this.value = this.value}",
          ),
        );

        //js to set focus in the text field...
        if (empty($form_state['values']['value'])) {
            drupal_add_js('jQuery(document).ready(function () {$("input:text:visible:first").focus();});', array(
              'type' => 'inline',
              'scope' => 'footer',
              'group' => JS_THEME,
              'weight' => 5,
            ));
        }
    }

    /*
      function query() {
      $this -> ensure_my_table();
      $where = "$this->table_alias.$this->real_field ";
      if ($this -> value != 'all') {
      $operator = '=';
      $this -> query -> add_where($this -> options['group'], $where, $this -> value, $operator);
      }
      } */

    function value_autocomplete($string) {

        $matches = array();
        $result = db_select('c_form_pendency')
            ->fields('c_form_pendency', array('customer_name', 'invoice_number'))
            ->condition('c_form_pendency.customer_name', '%' . db_like($string) . '%', 'LIKE')
            ->range(0, 50)
            ->execute();

        // save the query to matches
        foreach ($result as $row) {
            $matches[$row->customer_name] = check_plain($row->customer_name);
        }

        // Return the result to the form in json
        drupal_json_output($matches);
    }

}
