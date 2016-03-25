<html>
<head>
  <title>Oak Wheather Ambient</title>
  <meta charset="UTF-8">
  <link rel="stylesheet" type="text/css" href="style.css">
  <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js" type="text/javascript"></script>
  <script src="http://code.highcharts.com/highcharts.js"></script>
  <script src="http://code.highcharts.com/modules/exporting.js"></script>
  <script type='text/javascript' > 
    var set_time = '576'; 
  </script>
  <script type="text/javascript" src="temperature.js" ></script>
  <script type="text/javascript" src="humidity.js" ></script>
  <script type="text/javascript" src="pressure.js" ></script>
  <script type="text/javascript" src="ambient.js" ></script>
</head>
<body>
  <div id="header"> 
    <div id="picture"></div>
    <div id="current">
      <?php 
        require_once('current_data.php');
        $temp = db_get_temp();
        $amb = db_get_amb();
        $hum = db_get_hum();
        $press = db_get_press();
        echo "<table class='current'>";
          echo "<tr>";
            echo "<td><b>Temperature:</b></td>";
            echo "<td class='current'>" . $temp . "	&degC</td>";
            echo "<td><b>Pressure:</b></td>";
            echo "<td class='current'>" . $press . " hPa</td>";
          echo "</tr>";
          echo "<tr>";
            echo "<td><b>Humidity:</b></td>";
            echo "<td class='current'>" . $hum . " %</td>";
            echo "<td><b>Ambient:</b></td>";
            echo "<td class='current'>" . $amb . " %</td>";
          echo "</tr>";
        echo "</table>";
      ?>
    </div>
  </div>
  <div id="content">
    <div id="menu">
      <ul> 
        <li><a href="index.php">Overview</a></li>
        <li><a href="temperature.php">Temperature</a></li>
        <li><a href="pressure.php">Pressure</a></li>
        <li><a href="humidity.php">Humidity</a></li>
        <li><a href="ambient.php">Ambient</a></li>
      </ul>
    </div>
    <div id="data">
      <div id="ambient" style="height: 80%; margin: 0 auto"></div>
    </div>
  </div> 
</body>
</html>
