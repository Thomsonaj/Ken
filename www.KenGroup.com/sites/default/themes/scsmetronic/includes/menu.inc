<?php

/**
 * Returns HTML for primary and secondary local tasks.
 *
 * @param $variables
 *   An associative array containing:
 *     - primary: (optional) An array of local tasks (tabs).
 *     - secondary: (optional) An array of local tasks (tabs).
 *
 * @ingroup themeable
 * @see menu_local_tasks()
 */
function scsmetronic_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="mix-filter">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

function scsmetronic_menu_link(array $variables) {
  static $use_menu_icons;
  if(!isset($use_menu_icons)) {
    $use_menu_icons = theme_get_setting('use_menu_icons');
  }
  $element = $variables['element'];
  $main_menu = isset($element['#main_menu']);
  $sub_menu = '';
  if ($element['#below']) {
    if ($main_menu) {
      $element['#below']['#attributes']['class'][] = 'dropdown-menu';
    }
    $sub_menu = drupal_render($element['#below']);
    if ($main_menu) {
      $sub_menu = str_replace('nav', 'dropdown-menu', $sub_menu);
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'][] = 'dropdown';
      $element['#localized_options']['attributes']['data-target'][] = '#';
      $element['#title'] .= '<b class="caret"></b>';
      $element['#localized_options']['html'] = TRUE;
    }
  }
  if (!$main_menu && in_array('active-trail', $element['#attributes']['class']) &&
    strpos($sub_menu, 'active') === FALSE) {
    $element['#attributes']['class'][] = 'active';
  }
  $icon = theme_get_setting($element['#href']);
  if (empty($icon)) {
    $icon = 'icon-caret-right';
  }
  $element['#localized_options']['html'] = TRUE;
  $element['#title'] = "<i class='awesome $icon'></i>" . $element['#title'];
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
