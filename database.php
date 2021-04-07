<!DOCTYPE html>

<html>
<head>
   <link rel="stylesheet" type="text/css" href="style.css?ts=<time()?>&quot">
    <title>Database</title>
</head>
    <body>
        <p class="Titolo"> TRACCIAMENTO GPS </p>
        
      <div class="topnav">
        <a href="home.php">Home</a>
        <a class="active" href="database.php">Database</a>
        <a href="galleria.php">Galleria</a>
        <a href="mappa.php">Mappa</a>
      </div>

       </br>
        
        <form method="post" name="cerca" action="risultatiRicerca.php" id="cerca">
           <table>
              <tbody>
                 <tr>
                    <td>id</td>
                    <td><input id="id" name="id"></td>
                    <td>batteria max</td>
                    <td><input id="batteria" name="batteria"></td>
                    <td>h_dop min</td>
                    <td><input id="h_dop" name="h_dop"></td>
                 </tr>
                 <tr>
                    <td>lat_1_min</td>
                    <td><input id="lat_1_min" name="lat_1_min"></td>
                    <td>lat_1 max</td>
                    <td><input id="lat_1_max" name="lat_1_max"></td> 
                 </tr>
                 <tr>
                    <td>lon_1 min</td>
                    <td><input id="lon_1_min" name="lon_1_min"></td>
                    <td>lon_1 max</td>
                    <td><input id="lon_1_max" name="lon_1_max"></td>
                 </tr>
                 <tr>
                    <td>lat_2 min</td>
                    <td><input id="lat_2_min" name="lat_2_min"></td>
                    <td>lat_2 max</td>
                    <td><input id="lat_2_max" name="lat_2_max"></td>
                 </tr>
                 <tr>
                    <td>lon_2 min</td>
                    <td><input id="lon_2_min" name="lon_2_min"></td>
                    <td>lon_2 max</td>
                    <td><input id="lon_2_max" name="lon_2_max"></td>
                 </tr>
                 <tr>
                    <td>lat_3 min</td>
                    <td><input id="lat_3_min" name="lat_3_min"></td>
                    <td>lat_3 max</td>
                    <td><input id="lat_3_max" name="lat_3_max"></td>
                 </tr>
                 <tr>
                    <td>lon_3 min</td>
                    <td><input id="lon_3_min" name="lon_3_min"></td>
                    <td>lon_3 max</td>
                    <td><input id="lon_3_max" name="lon_3_max"></td>
                 </tr>
                 
              </tbody>
           </table> </br>
           
           <form method="get" action="risultatiRicerca.php"><button type="submit">cerca</button></form></br>
           
        </form>
        


    </body>
</html>
