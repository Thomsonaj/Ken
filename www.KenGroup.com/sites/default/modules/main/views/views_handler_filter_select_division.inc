<?php
/*
class views_handler_filter_select_division extends views_handler_filter_boolean_operator {
  function construct() {
    $this -> value_value = t('Select Division');
    parent::construct();
  }

  function get_value_options() {
  $divs = db_select('c_form_pendency', 'e')
        ->fields('e', array('division'))//SELECT the fields from node
        ->distinct()
        ->condition('division', NULL, 'IS NOT')
        ->orderBy('e.division', 'ASC')
        ->execute();
    $divisions = array();
    foreach ($divs as $div) {
        foreach ($div as $d) {
            $divisions[$d] = $d;
        }
    }
      $this -> value_options = $divisions;
  }

  function value_form(&$form, &$form_state) {
    // Initialize the array of possible values for this filter.
    $this -> get_value_options();
    
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Select Division'),
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
 
 */