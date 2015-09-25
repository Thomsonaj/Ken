<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * get a flower by id and return the object
 */

//function myservice_get_flower($fid) {
//  return db_select('flower', 'f')->fields('f',array('fid','fname','fcolor'))->condition('fid', $fid)->execute()->fetchField();
//}
//function _myservice_flower_retrieve($id) {
//      return myservice_get_flower($fid);
//    }


function _myservice_display() {
  // dpm('swati');
  // watchdog('php', 'cominghere');
  return array("message" => "hiii");
}

function _myservice_create_flower($data) {
  // function _noteresource_create($data) {
  watchdog('php', var_export($data));
  watchdog('php', 'cominghere create');

  if (!isset($data)) {
    return services_error('Missing data');
  }
  else {
    return array("data set");
  }
}

// dpm($test);
//  global $user;
//  $data['uid'] = $user->uid;
//  $data->fname = 'fname';
//  $data->color = 'color';
// 
//  _myservice_create($fdata);
//doubt
//  return (object) array(
//      'id' => $data->id,
//      'uri' => services_service_uri(array('data', $data->id)),
//  );
// return array("message" => "hiii");
//$name;
//if (isset($data) &&  is_array($data)) $data=(object) $data;
//return ("data is");
function _myservice_create($fdata) {
  drupal_write_record('flower', $fdata);
}

function _test_function($name) {
  watchdog('php', $name);
  return "test";
}

function _myservice_retrive_flower($fid) {
  watchdog('php', 'cominghere in retrive');
  // drupal_set_message(print_r($fid));
  return _myservice_flowerdetails($fid);
}

function _myservice_flowerdetails($fid) {
  $res = db_select('flower', 'f')->fields('f', array('fname'))->condition('fid', $fid)->execute()->fetchField();
  //$flr = $res->fetchAll();
  watchdog('php', '$res');
  return $res;
}

function _myservice_retrive_flower_id($fid) {
  // drupal_set_message(print_r($fid));
  $fname = $fid[0]['fname'];
  $fcolor = $fid[1]['color'];
  drupal_set_message(print_r($fname . $fcolor));
  return _myflower_flower_insert($fname, $fcolor);
  //return $fid;
}

function _myflower_flower_insert($fname, $fcolor) {

  //return $fname.$fcolor;
  global $user;
  try {

    $q = db_select('flower', 'f')->fields('f', array('fid'))->condition('fname', $fname)->condition('color', $fcolor)
        ->execute()->fetchField();
    if (isset($q) && is_numeric($q)) {
      drupal_set_message(print_r($user));
      return "ths name and color combination is already inserted";
    }
    else {
      $res = db_insert('flower')->fields(array('fname' => $fname, 'color' => $fcolor, 'uid' => $user->uid))->execute();
    }
  }
  catch (Exception $ex) {
    watchdog('php', $ex);
    drupal_set_message('not successfu');
  }

  return "inserted flower id is " . $res . "flower name is " . $fname;
}
