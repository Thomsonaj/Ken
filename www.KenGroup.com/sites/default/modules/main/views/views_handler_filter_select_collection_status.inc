<?php

class views_handler_filter_select_collection_status extends views_handler_filter_boolean_operator {

    function construct() {
        $this->value_value = t('Select Collection Status');
        parent::construct();
    }

    function get_value_options() {
        $collection_status = array(0 => 'Collected', 1 => 'Not Collected');
        $this->value_options = $collection_status;
    }

    function value_form(&$form, &$form_state) {
        // Initialize the array of possible values for this filter.
        $this->get_value_options();

        $form['value'] = array(
          '#type' => 'select',
          '#title' => t('Select Collection Status'),
          '#options' => $this->value_options,
          '#default_value' => '',
        );
    }

    function query() {
        $this->ensure_my_table();
        $where = "$this->table_alias.$this->real_field ";
        // dsm($this->options['group']);
        $current_timestamp = time();
        if ($this->value != 'all') {

            if ($this->value == 0 && !empty($this->options['group'])) {
                $operator = '<=';
                $this->query->add_where($this->options['group'], $where, $current_timestamp, $operator);
            }
            else if ($this->value == 1) {
                $operator = '>=';
               // $this->query->add_where($this->options['group'],$where, NULL, 'IS');
                    //->condition($this->options['group'],$where, $current_timestamp, $operator);
              // $this->query->add_where(1, $or);
                // $this->query->add_where($this->options['group'], $where, NULL, 'IS') ;
                 $this->query->add_where($this->options['group'], $where, $current_timestamp, $operator) ;
                    // $this->query->add_where($this->options['group'],$where, NULL, 'IS');
                // $this->query->add_where($this->options['group'], $where, $current_timestamp, $operator);
            }
            // $operator = '<=';
            //   $this->query->add_where($this->options['group'], $where, $current_timestamp, $operator);
        }
    }

}
