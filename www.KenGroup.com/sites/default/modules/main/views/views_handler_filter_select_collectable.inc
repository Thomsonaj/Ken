<?php

class views_handler_filter_select_collectable extends views_handler_filter_boolean_operator {
  function construct() {
    $this -> value_value = t('Select Collectable');
    parent::construct();
  }

  function get_value_options() {
       
      $this -> value_options = arr_collectable();
  }

  function value_form(&$form, &$form_state) {
    // Initialize the array of possible values for this filter.
    $this -> get_value_options();
    
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Select Collectable'),
      '#options' => $this -> value_options,
      '#default_value' => '',
    );
  }
function query() {
    $this -> ensure_my_table();
    $where = "$this->table_alias.$this->real_field ";
    if ($this -> value != 'all') {
      $operator = '=';
      $this -> query -> add_where($this -> options['group'], $where, $this -> value, $operator);
    }
  }
}