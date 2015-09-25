<?php

class views_handler_filter_select_quarter extends views_handler_filter_boolean_operator {

    function construct() {
        $this->value_value = t('Select Quarter');
        parent::construct();
    }

    function get_value_options() {
        $quarter = array('q1'=>'Quarter 1', 'q2'=>'Quarter 2', 'q3'=>'Quarter 3', 'q4'=>'Quarter 4');
        $this->value_options = $quarter;
    }

    function value_form(&$form, &$form_state) {
        // Initialize the array of possible values for this filter.
        $this->get_value_options();

        $form['value'] = array(
          '#type' => 'select',
          '#title' => t('Select Quarter'),
          '#options' => $this->value_options,
          '#default_value' => '',
        );
    }

    function query() {
        $this->ensure_my_table();
        $where = "$this->table_alias.$this->real_field ";
        if ($this->value != 'all') {
            $operator = 'like';
            $this->query->add_where($this->options['group'], $where, $this->value.'%', $operator);
        }
    }

}
