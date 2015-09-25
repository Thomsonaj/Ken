<?php

class views_handler_filter_select_finantial_year extends views_handler_filter_boolean_operator {
  function construct() {
    $this -> value_value = t('Select financial year');
    parent::construct();
  }

  function get_value_options() {
  $years = db_select('c_form_pendency', 'e')
        ->fields('e', array('finantial_year'))//SELECT the fields from node
        ->distinct()
        ->condition('finantial_year', NULL, 'IS NOT')
        ->orderBy('e.finantial_year', 'ASC')
        ->execute();
    $finantial_year = array();
    foreach ($years as $year) {
        foreach ($year as $yr) {
            $finantial_year[$yr] = $yr;
        }
    }
      $this -> value_options = $finantial_year;
  }

  function value_form(&$form, &$form_state) {
    // Initialize the array of possible values for this filter.
    $this -> get_value_options();
    
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Select financial year'),
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