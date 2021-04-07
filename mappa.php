<!DOCTYPE html>
<html>
<head>
	
	<?php
	$lat = $_REQUEST["lat"];
    $lng = $_REQUEST["lng"];
    
	 ?>
    <link rel="stylesheet" type="text/css" href="style.css?ts=<time()?>&quot">
    <script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?sensor=false"></script>
    
    <script type="text/javascript">
		function parseGetVars(){
		var args = new Array();
		var query = window.location.search.substring(1);
		
		if (query) {
			var strList = query.split('&');
			for (str in strList){
				var parts = strList[str].split('=');
				args[unescape(parts[0])] = unescape(parts[1])
			}
		}
		return args;
	} 
    </script>
    
    <script type="text/javascript">
		
		var pos = parseGetVars();
		var sito = get['mappa.php'];
    function initialize(){
		//document.getElementById("$_REQUEST");
		var pos = parseGetVars();
		var myLatLng = new google.maps.LatLng(42,12.50843);
		//var myLatLng1 = new google.maps.LatLng(pos[0],pos[1]);
		var myOptions = { zoom: 14, center: myLatLng, mapTypeId: google.maps.MapTypeId.ROADMAP}
		var map = new google.maps.Map(document.getElementById("gmaps-canvas"),myOptions);
		var marker = new google.maps.Marker({position: myLatLng, map: map, title:"Mi trovo a Roma"});
	}
    </script>

    <title><?php echo "Mappa"; ?></title>
</head>
<body onload="initialize()">
    <p class="Titolo">TRACCIAMENTO GPS</p>
    
    <div class="topnav">
        <a href="home.php">Home</a>
        <a href="database.php">Database</a>
        <a href="galleria.php">Galleria</a>
        <a class="active" href="mappa.php">Mappa</a>
    </div>
    
    </br>
    
    <div id="gmaps-canvas"></div>
    
    </br>
    
</body>
 <form method="post" name="cerca" action="mappa.php" id="cerca">
           <table>
              <tbody>
                 <tr>
                    <td>lat</td>
                    <td><input id="lat" name="lat"></td>
                 </tr>
                 <tr>
                    <td>lng</td>
                    <td><input id="lng" name="lng"></td>
                 </tr>
              </tbody>
           </table> </br>
           
           <form method="get" action="mappa.php"><button type="submit">cerca</button></form></br>
           
        </form>




	<?php
	echo $lat;
	echo "</br>";
	echo $lng;
	?>
</html>
