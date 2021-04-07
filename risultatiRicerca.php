<!DOCTYPE html>
<html>
<head> 
<link rel="stylesheet" type="text/css" href="style.css?ts=<time()?>&quot">
<title>Risultati Ricerca</title>
</head>
   <body>
	   <p class="Titolo"> Risultati Ricerca </p>
	   
	  <div class="topnav">
		<a href="home.php">Home</a>
        <a href="database.php">Database</a>
        <a href="galleria.php">Galleria</a>
        <a href="mappa.php">Mappa</a>
      </div>
      
      </br>
     <p> Mostra tutto
      <form method="get" action="risultatiRicerca.php"><button type="submit">Vai</button></form></br>
	  </p>   
	   <?php
	   
	   // recupero i dati dalla form
	   $id = $_REQUEST["id"];
	   $batteria = $_REQUEST["batteria"];
	   $h_dop = $_REQUEST["h_dop"];
	   $lat_1_min = $_REQUEST["lat_1_min"];
	   $lat_1_max = $_REQUEST["lat_1_max"];
	   $lon_1_min = $_REQUEST["lon_1_min"];
	   $lon_1_max = $_REQUEST["lon_1_max"];
	   $lat_2_min = $_REQUEST["lat_2_min"];
	   $lat_2_max = $_REQUEST["lat_2_max"];
	   $lon_2_min = $_REQUEST["lon_2_min"];
	   $lon_2_max = $_REQUEST["lon_2_max"];
	   $lat_3_min = $_REQUEST["lat_3_min"];
	   $lat_3_max = $_REQUEST["lat_3_max"];
	   $lon_3_min = $_REQUEST["lon_3_min"];
	   $lon_3_max = $_REQUEST["lon_3_max"];

	   
	   $host  = 'localhost';
       $user  = 'ale';
       $psw   = '11235813213455';
       $db    = 'dataTrack';
	   
	   $con = mysqli_connect($host, $user, $psw, $db);
	   
       if (!$con) {
           mysqli_close($con);
           die('Non riesco a connettermi: '.mysqli_errno());        
       }
       else {
           echo "Connesso al database: dataTrack</br></br>";
       }
       
       $query = "SELECT * FROM infoTrack WHERE preambolo='77' ";
       
       if ($id) {
		   $query = $query . "AND id='$id'";
	   }
	   
	   if ($batteria) {
		   $query = $query . "AND batt<='$batteria'";
	   }
	   
	   if ($h_dop) {
		   $query = $query . "AND h_dop>='$h_dop'";
	   }
	   
	   if ($lat_1_min) {
		   $query = $query . "AND lat_1>='$lat_1_min'";
	   }
	   if ($lat_1_max) {
		   $query = $query . "AND lat_1<='$lat_1_max'";
	   }
	   if ($lon_1_min) {
		   $query = $query . "AND lon_1>='$lon_1_min'";
	   }
	   if ($lon_1_max) {
		   $query = $query . "AND lon_1<='$lon_1_max'";
	   }
	   if ($lat_2_min) {
		   $query = $query . "AND lat_2>='$lat_2_min'";
	   }
	   if ($lat_2_max) {
		   $query = $query . "AND lat_2<='$lat_2_max'";
	   }
	   if ($lon_2_min) {
		   $query = $query . "AND lon_2>='$lon_2_min'";
	   }
	   if ($lon_2_max) {
		   $query = $query . "AND lon_2<='$lon_2_max'";
	   }
	   if ($lat_3_min) {
		   $query = $query . "AND lat_3>='$lat_3_min'";
	   }
	   if ($lat_3_max) {
		   $query = $query . "AND lat_3<='$lat_3_max'";
	   }
	   if ($lon_3_min) {
		   $query = $query . "AND lon_3>='$lon_3_min'";
	   }
	   if ($lon_3_max) {
		   $query = $query . "AND lon_3<='$lon_3_max'";
	   }
	   $query = $query . ";";
	   
       $result   = mysqli_query($con,$query);
       $n_fields = mysqli_num_fields($result);
       
       if (!$result) {
           mysqli_close($con);
           die('Errore: '.mysqli_errno());
       }	   
	   
	   echo "Query: ". $query. "</br></br>"; 
	   
	   
	   
	   echo "<table>";
       echo "<tr><td colspan='$n_fields'>infoTrack</td> </tr>";
       echo "<tr>",
            "<td>unixTime</td>",
            "<td>preambolo</td>",
			//"<td>sec</td>",
			"<td>n_reboot</td>",
            "<td>id</td><td>batteria</td><td>h_dop</td>",
            "<td>lat_1</td><td>lon_1</td>",
			//"<td>lat_2</td>",
            //"<td>lon_2</td><td>lat_3</td><td>lon_3</td>",
            "</tr> \n";
            
       while ($row = mysqli_fetch_array($result)) {
          echo "<tr>";
          echo "<td>" . $row['unixTime']. "</tdtd>";
          echo "<td>" . $row['preambolo']. "</td>";
          //echo "<td>" . $row['sec']. "</td>";
          echo "<td>" . $row['n_reboot']. "</td>";
          echo "<td>" . $row['id']. "</td>";
          echo "<td>" . $row['batt']. "</td>";
          echo "<td>" . $row['h_dop']. "</td>";
          echo "<td>" . $row['lat_1']. "</td>";
          echo "<td>" . $row['lon_1']. "</td>";
         // echo "<td>" . $row['lat_2']. "</td>";
         // echo "<td>" . $row['lon_2']. "</td>";
         // echo "<td>" . $row['lat_3']. "</td>";
         // echo "<td>" . $row['lon_3']. "</td>";
          echo "</tr>";
       }                                           
       echo "</table></br></br>";            
            
       mysqli_free_result($result);
            
       
	   ?>
	   
	   
	   
	   
	   
   </body>


</html>
