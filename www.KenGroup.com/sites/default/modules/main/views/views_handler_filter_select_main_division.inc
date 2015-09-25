<?php
/*
class views_handler_filter_select_main_division extends views_handler_filter_boolean_operator {
  function construct() {
    $this -> value_value = t('Select main division');
    parent::construct();
  }

  function get_value_options() {
  $main_division = db_select('c_form_pendency', 'e')
        ->fields('e', array('main_division'))//SELECT the fields from node
        ->distinct()
        ->condition('main_division', NULL, 'IS NOT')
        ->orderBy('e.main_division', 'ASC')
        ->execute();
    $main_div = array();
    foreach ($main_division as $mdivsion) {
        foreach ($mdivsion as $md) {
            $main_div[$md] = $md;
        }
    }
      $this -> value_options = $main_div;
  }

  function value_form(&$form, &$form_state) {
    // Initialize the array of possible values for this filter.
    $this -> get_value_options();
    
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Select Main Division'),
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
 * 
 */