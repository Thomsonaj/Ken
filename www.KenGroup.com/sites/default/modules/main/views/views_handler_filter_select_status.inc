<?php

class views_handler_filter_select_status extends views_handler_filter_boolean_operator {
  function construct() {
    $this -> value_value = t('Select Status');
    parent::construct();
  }

  function get_value_options() {
    //to truncate string in list
     /* $trunc_array= array();
      $i=1;
      foreach (arr_status() as $ss){
          if(strlen($ss)>30){
          $trunc_array[$i] = substr($ss,0,27).'...';
          }else{
              $trunc_array[$i] = $ss;
          }
          $i++;
      }
   
      $this -> value_options = $trunc_array;
     */
     //normal list without truncation
      $this -> value_options = arr_status();
  }

  function value_form(&$form, &$form_state) {
    // Initialize the array of possible values for this filter.
    $this -> get_value_options();
    
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Select Status'),
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