<?php
function db_connect() {
  static $connection;
    
  if(!isset($connection)) 
  {
    $config = parse_ini_file('../config.ini'); 
    $connection = mysqli_connect('localhost',$config['username'],$config['password'],$config['dbname']);
  }

  if($connection === false) 
  {
    return mysqli_connect_error(); 
  }
  return $connection;
}

function db_query($query) 
{
  $connection = db_connect();
  $result = mysqli_query($connection,$query);
  return $result;
}

function db_get_temp() 
{
  $result = db_query("SELECT temperature FROM weather ORDER BY date DESC LIMIT 1");
  $value = mysqli_fetch_object($result);
  return $value->temperature;
}

function db_get_amb() 
{
  $result = db_query("SELECT ambient FROM weather ORDER BY date DESC LIMIT 1");
  $value = mysqli_fetch_object($result);
  return $value->ambient;
}

function db_get_hum() 
{
  $result = db_query("SELECT humidity FROM weather ORDER BY date DESC LIMIT 1");
  $value = mysqli_fetch_object($result);
  return $value->humidity;
}

function db_get_press() 
{
  $result = db_query("SELECT pressure FROM weather ORDER BY date DESC LIMIT 1");
  $value = mysqli_fetch_object($result);
  return $value->pressure;
}
