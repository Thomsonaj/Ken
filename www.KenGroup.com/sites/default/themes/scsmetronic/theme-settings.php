<?php

/**
 * Allow themes to alter the theme-specific settings form.
 *
 * With this hook, themes can alter the theme-specific settings form in any way
 * allowable by Drupal's Form API, such as adding form elements, changing
 * default values and removing form elements. See the Form API documentation on
 * api.drupal.org for detailed information.
 *
 * Note that the base theme's form alterations will be run before any sub-theme
 * alterations.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function scsmetronic_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['scsmetronic_theme_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metronic Theme Settings'),
  );
  $form['scsmetronic_theme_settings']['theme_header'] = array(
    '#type' => 'radios',
    '#title' => t('Header'),
    '#options' => array(
      'default' => t('Default'),
      'fixed' => t('Fixed'),
    ),
    '#default_value' => theme_get_setting('theme_header'),
    '#description' => t('Specify whether the header will be fixed to the top on scroll of page'),
  );
  $form['scsmetronic_theme_settings']['theme_footer'] = array(
    '#type' => 'radios',
    '#title' => t('Footer'),
    '#options' => array(
      'default' => t('Default'),
      'fixed' => t('Fixed'),
    ),
    '#default_value' => theme_get_setting('theme_footer'),
    '#description' => t('Specify whether the footer will be fixed to the bottom on scroll of page'),
  );
  $form['scsmetronic_theme_settings']['theme_sidebar'] = array(
    '#type' => 'radios',
    '#title' => t('Sidebar'),
    '#options' => array(
      'default' => t('Default'),
      'fixed' => t('Fixed'),
      'closed' => t('Closed'),
    ),
    '#default_value' => theme_get_setting('theme_sidebar'),
    '#description' => t('Specify whether the sidebar will be fixed, closed to the left on scroll of page'),
  );
  $form['scsmetronic_theme_settings']['theme_right_sidebar'] = array(
    '#type' => 'radios',
    '#title' => t('Right Sidebar'),
    '#options' => array(
      'default' => t('Default'),
      'fixed' => t('Fixed'),
      'closed' => t('Closed'),
    ),
    '#default_value' => theme_get_setting('theme_right_sidebar'),
    '#description' => t('Specify whether the right sidebar will be fixed, closed to the left on scroll of page'),
  );
  $menus = menu_get_menus();
  $form['scsmetronic_theme_settings']['theme_main_menu'] = array(
    '#type' => 'select',
    '#options' => $menus, 
    '#title' => t('Select menu to show as Main Menu'),
    '#default_value' => theme_get_setting('theme_main_menu'),
    '#description' => t(''),
    '#empty_option' => t('Select'),
    '#empty_value' => 0,
  );
  $form['scsmetronic_theme_settings']['theme_modal'] = array(
    '#type' => 'textarea',
    '#title' => t('Launch Modal'),
    '#description' => t('Enter the one URL per line that needs must be launched in modal frame'),
    '#default_value' => theme_get_setting('theme_modal'),
  );
}
