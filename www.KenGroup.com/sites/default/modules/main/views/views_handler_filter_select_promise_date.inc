<?php

class views_handler_filter_select_promise_date extends views_handler_filter_boolean_operator {

    function construct() {
        $this->value_value = t('Select Promise Date');
        parent::construct();
    }

    function get_value_options() {
        
    }

    function value_form(&$form, &$form_state) {
        $form['value'] = array(
          '#title' => t('Promise Date'),
          '#type' => 'date_popup',
          '#date_format' => 'd-m-Y',
          '#date_label_position' => 'within',
        );
    }

    function query() {
        $ken_promise_date = isset($this -> value) ? strtotime($this -> value) : 0;
      $this -> ensure_my_table();
    $where = "$this->table_alias.$this->real_field ";
    if (!empty($ken_promise_date)) {
      $operator = '=';
      $this -> query -> add_where($this -> options['group'], $where, $ken_promise_date, $operator);
    }
    }

}
