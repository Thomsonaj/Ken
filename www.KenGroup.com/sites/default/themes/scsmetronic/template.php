<?php

$theme_path = drupal_get_path('theme', 'scsmetronic');
require_once $theme_path . '/includes/menu.inc';
require_once $theme_path . '/includes/theme.inc';
require_once $theme_path . '/includes/form.inc';

//if (module_exists("views") && module_exists("views_data_export_csv"))
//  require_once $theme_path . '/includes/views/views_export_csv_plugin_style_csv.inc';

/**
 * Preprocess variables for html.tpl.php
 *
 * @see system_elements()
 * @see html.tpl.php
 */
function scsmetronic_preprocess_html(&$variables) {
  // Add conditional JS for IE
  drupal_add_js(path_to_theme() . '/assets/plugins/respond.min.js', array('group' => JS_THEME, 'browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_js(path_to_theme() . '/assets/plugins/excanvas.min.js', array('group' => JS_THEME, 'browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE), 'preprocess' => FALSE));

  if ($variables['logged_in']) {
    //Set the default classes for the page
    $theme_header = theme_get_setting('theme_header', 'scsmetronic');
    $theme_footer = theme_get_setting('theme_footer', 'scsmetronic');
    $theme_sidebar = theme_get_setting('theme_sidebar', 'scsmetronic');
    $theme_right_sidebar = theme_get_setting('theme_right_sidebar', 'scsmetronic');
    $theme_values = array('page-sidebar-fixed', 'page-sidebar-closed', 'page-footer-fixed', 'page-header-fixed');
    foreach ($theme_values as $value) {
      $key = array_search($value, $variables['classes_array']);
      if ($key !== FALSE) {
        unset($variables['classes_array'][$key]);
      }
    }
    if (!empty($theme_header) && $theme_header !== 'default') {
      $variables['classes_array'][] = "page-header-" . $theme_header;
      $variables['navbar_top'] = 'navbar-fixed-top';
    }
    if (!empty($theme_sidebar) && $theme_sidebar !== 'default') {
      $variables['classes_array'][] = "page-sidebar-" . $theme_sidebar;
    }
    if (!empty($theme_right_sidebar) && $theme_right_sidebar !== 'default') {
      $variables['classes_array'][] = "page-sidebar-" . $theme_right_sidebar;
    }
    if (!empty($theme_footer) && $theme_footer !== 'default' && $theme_sidebar !== 'fixed') {
      $variables['classes_array'][] = "page-footer-" . $theme_footer;
    }
    $tmm = theme_get_setting('theme_main_menu', 'scsmetronic');
    if (empty($tmm) && in_array('no-sidebars', $variables['classes_array'])) {
      unset($variables['classes_array']['no-sidebars']);
      $variables['classes_array'][] = 'page-full-width';
    }
  }
  else {
    $variables['classes_array'][] = 'login';
  }
}

/**
 * Processes variables for block.tpl.php.
 *
 * Prepares the values passed to the theme_block function to be passed
 * into a pluggable template engine. Uses block properties to generate a
 * series of template file suggestions. If none are found, the default
 * block.tpl.php is used.
 *
 * Most themes utilize their own copy of block.tpl.php. The default is located
 * inside "modules/block/block.tpl.php". Look in there for the full list of
 * variables.
 *
 * The $variables array contains the following arguments:
 * - $block
 *
 * @see block.tpl.php
 */

function scsmetronic_preprocess_page(&$variables) {
  global $user;
  if (variable_get('scsmetronic_redirect_to_login') && $user->uid == 0 && arg(0) != 'user') {
    //header('Location: ' . url('user/login', array( 'absolute' => TRUE)), TRUE, 302);
    // Handle redirection to the login form.
    // using drupal_goto() with destination set causes a recursive redirect loop
    $login_path = 'user/login';
    $code = 302;
    // The code in drupal_get_destination() doesn't preserve any query string
    // on 403 pages, so reproduce the part we want here.
    $path = isset($_GET['destination'])? $_GET['destination'] : '<front>';
    $query = drupal_http_build_query(drupal_get_query_parameters(NULL, array('q', 'destination')));
    if ($query != '') {
      $path .= '?' . $query;
    }
    $destination = array('destination' => $path);
    header('Location: ' . url($login_path, array('query' => $destination, 'absolute' => TRUE)), TRUE, 302);
    drupal_exit();
  }
  $variables['navbar_top'] = 'navbar-static-top';
  $theme_header = theme_get_setting('theme_header', 'scsmetronic');
  if (!empty($theme_header) && $theme_header !== 'default') {
    $variables['navbar_top'] = 'navbar-fixed-top';
  }
  //Get the entire main menu tree
  $main_menu_name = theme_get_setting('theme_main_menu', 'scsmetronic');
  $main_menu_tree = menu_tree_all_data($main_menu_name);
  $user_menu_tree = menu_tree_all_data('user-menu');

//Add the rendered output to the $main_menu_expanded variable
  $variables['main_menu_expanded'] = menu_tree_output($main_menu_tree);
  $variables['user_menu_expanded'] = menu_tree_output($user_menu_tree);
  if (($modal_form_paths = theme_get_setting('theme_modal'))) {
    $modal_forms = explode("\r\n", $modal_form_paths);
    drupal_add_js(array('scsmetronic_forms_modal' => $modal_forms), 'setting');
  }

  if ($user->uid) {
    $name = theme('username', array('account' => $user, 'link_path' => NULL));
  }
  else {
    $name = variable_get('anonymous', t('Guest'));
  }
  $variables['loggedin_user_name'] = $name;
  $variables['image'] = scsmetronic_login_user_image($user); 
}

function scsmetronic_links__system_main_menu($variables) {
  $action_links = menu_link_get_preferred($_GET['q']); //for getting th eparent link for menu local action.
  $parent_link = $action_links['tab_parent_href'];
  $toggler = '';
  $modal = theme_get_setting('theme_modal');
  $modal_array = explode("\n", $modal);
  if (isset($variables['links'])) {

    $sub_menu = FALSE;
    $links = $variables['links'];
    $ulclass = 'page-sidebar-menu ';
    $toggler = '<li><div class="sidebar-toggler hidden-phone"></div></li>';
  }
  else {
    $sub_menu = TRUE;
    $links = $variables;
    $ulclass = 'sub-menu ';
  }

  $html = '<ul class="' . $ulclass . '">';
  
  $html .= $toggler;
  foreach ($links as $key => $link) {
    if (is_numeric($key)) {
      $href = $link['#href'];
      $title = $link['#title'];
      $liclass = $link['#attributes']['class'];
      $below = $link['#below'];

      $linkclass = '';
      if (in_array('first', $liclass))
        $linkclass = 'start ';
      if (in_array('last', $liclass))
        $linkclass = 'last ';

      $selected = '';
      
      if (isset($link['#href']) && (($link['#href'] == current_path()) || $link['#href'] == $parent_link)) {
        $linkclass .= 'active ';
        $selected = '<span class="selected"></span>';
      }
      $arrow = '';
      $check = false;
      if (!empty($below)) {
        $arrow = '<span class="arrow "></span>';
        if (scsmetronic_check_below($below)) {
          $linkclass .= 'active ';
          $selected = '<span class="selected"></span>';
          $arrow = '<span class="arrow open"></span>';
        }
      }

      $icon = '';
      if (!$sub_menu) {
        if (!empty($link['#localized_options']) && !empty($link['#localized_options']['icon']))
          $icon = '<i class="fa ' . $link['#localized_options']['icon'] . '"></i>';
        else
          $icon = '<i class="fa fa-arrow-circle-right"></i>';
      }
      $title = $icon . '<span class="title">' . $title . '</span>' . $selected . $arrow;
      foreach ($modal_array as $m_array) {
        $mo_array[] = trim($m_array);
      }
      if (in_array($href, $mo_array)) {
        $output = l($title, $href, array("html" => TRUE, 'attributes' => array("data-toggle" => "modal")));
      }
      else {
        $output = l($title, $href, array("html" => TRUE,));
      }

      if (!empty($below)) {
        $output = '<a href="javascript:;">' . $title . '</a>';
      }
      $html .= '<li class="' . $linkclass . ' ">' . $output;
      if (!empty($below)) {
        $html .= scsmetronic_links__system_main_menu($below);
      }
      $html .='</li>';
    }
  }
  $html .= '</ul>';
  return $html;
}

function scsmetronic_views_data_export_feed_icon($variables) {
  extract($variables, EXTR_SKIP);
  $url_options = array('html' => true);
  if ($query) {
    $url_options['query'] = $query;
  }
  $image = theme('image', array('path' => $image_path, 'alt' => $text, 'title' => $text));
  return l('Export to ' . $variables['text'], $url, $url_options);
//  return l('Export to'.$variables['text'], $this->view->get_url(NULL, $path), $url_options);
}

function scsmetronic_check_below($below) {
  $exists = FALSE;
  foreach ($below as $skey => $slink) {
    if (is_numeric($skey)) {
      if (isset($slink['#href']) && ($slink['#href'] == current_path())) {
        $exists = TRUE;
        break;
      }
      elseif (!empty($slink['#below'])) {
        $exists = scsmetronic_check_below($slink['#below']);
      }
    }
    if ($exists)
      break;
  }
  return $exists;
}

function scsmetronic_links__system_user_menu($variables) {
  $html = '<ul class="dropdown-menu">';
  $html .= '<li><a href="javascript:;" id="trigger_fullscreen"><i class="fa fa-move"></i> Full Screen</a></li><li class="divider"></li>';
  foreach ($variables['links'] as $key => $link) {
    if (is_numeric($key)) {
      $href = $link['#href'];
      $title = $link['#title'];
      $icon = '<i class="fa fa-home"></i> ';
      $title = $icon . $title;
      $output = l($title, $href, array("html" => TRUE));
      $html .= '<li>' . $output . '</li>';
    }
  }
  $html .= '</ul>';
  return $html;
}

function scsmetronic_theme() {
  $items = array();
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'scsmetronic') . '/templates/user',
    'template' => 'user-login',
  );
  $items['user_pass'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'scsmetronic') . '/templates/user',
    'template' => 'user-pass',
  );
  return $items;
}

/**
 * over ride the item list to exclude the otuside tag
 */
function scsmetronic_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $add_div = (isset($variables['add_div']) ? $variables['add_div'] : TRUE);
  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = $add_div ? '<div class="item-list">' : '';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  $output .= $add_div ? '</div>' : '';
  return $output;
}

function scsmetronic_login_user_image($user) {
  if(!empty($user->picture)){
  $query = db_select('file_managed', 'fm')->fields('fm', array('uri'))->condition('fid', $user->picture);
  $link = $query->execute()->fetchField();
  return $link;
  }
}

/**
 * override theme_usernamne.
 */
function scsmetronic_username (&$variables) {
  if (isset($variables['link_path']) && (!isset($variables['show_link']) || $variables['show_link'])) {
    // We have a link path, so we should generate a link using l().
    // Additional classes may be added as array elements like
    // $variables['link_options']['attributes']['class'][] = 'myclass';
    $output = l($variables['name'] . $variables['extra'], $variables['link_path'], $variables['link_options']);
  }
  else {
    // Modules may have added important attributes so they must be included
    // in the output. Additional classes may be added as array elements like
    // $variables['attributes_array']['class'][] = 'myclass';
    $output = '<span' . drupal_attributes($variables['attributes_array']) . '>' . $variables['name'] . $variables['extra'] . '</span>';
  }
  return $output;
}
