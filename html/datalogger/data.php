<?php
static $connection;

if(!isset($connection)) 
{
  $config = parse_ini_file('../config.ini'); 
  $connection = mysqli_connect('localhost',$config['username'],$config['password'],$config['dbname']);
}

if($connection === false) 
{
  die('DB connection not possible: ' . mysqli_error());
}

$identifier = $_REQUEST['identifier'];
$time = $_REQUEST['time'];
$query = "SELECT * FROM (SELECT * FROM weather ORDER BY date DESC LIMIT $time) sub ORDER BY date ASC";
$result = mysqli_query($connection,$query);

while($row = mysqli_fetch_array($result))
    {
      echo $row['date'] . "/" . $row[$identifier]. "/" ;
    }
mysqli_close($connection);

?>
