<?php

/**
 * Returns HTML for a breadcrumb trail.
 *
 * @param $variables
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 */
function scsmetronic_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    $breadcrumbs = '<ul class="page-breadcrumb breadcrumb">';
    $count = count($breadcrumb) - 1;
    foreach ($breadcrumb as $key => $value) {
      $icon = "";
      if ($key === 0) {
        $icon = '<i class="fa fa-home"></i> ';
      }
      if ($count != $key) {
        $breadcrumbs .= '<li>' . $icon . $value . '<i class="fa fa-angle-right"></i></li>';
      }
      else {
        $breadcrumbs .= '<li>' . $icon . $value . '</li>';
      }
    }
    $breadcrumbs .= '</ul>';
    return $breadcrumbs;
  }
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 */
function scsmetronic_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );

  // Map Drupal message types to their corresponding Bootstrap classes.
  // @see http://twitter.github.com/bootstrap/components.html#alerts
  $status_class = array(
    'status' => 'success',
    'error' => 'danger',
    'warning' => 'warning',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';
    $output .= "<div class=\"alert alert-block $class fade in\">\n";
    $output .= " <button class=\"close\" data-dismiss=\"alert\"></button>\n";
    //$output .= " <h4 class=\"alert-heading\">$status_class[$type]!</h4>\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }

    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }

    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Display a view as a table style.
 */
function scsmetronic_preprocess_views_view_table(&$variables) {
  $key = array_search('views-table', $variables['classes_array']);
  if ($key !== FALSE) {
    unset($variables['classes_array'][$key]);
  }
  $variables['classes_array'] = array_merge($variables['classes_array'], array('table', 'table-striped', 'table-bordered', 'table-hover', 'dataTable'));
}
