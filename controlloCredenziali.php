<html>
<head>
    <link rel="stylesheet" type="text/css" href="style.css?ts=<time()?>&quot">
    <title>Controllo Credenziali di Accesso </title>
</head>
<body>
    
   <?php
   //tutte le variabili sono identificate dal simbolo "$" e non devono essere dichiarati i tipi
   $user = $_REQUEST["user"];   // $_REQUEST è il "vettore associativo" dove vengono memorizzati i caratteri inseriti. Alternativamente si può usare $_POST
   $psw = $_REQUEST["psw"];     // gli elementi di $_REQUEST sono chiamati come i name inseriti nella form
    
   
   if ($user=="Alessandro" && $psw=="11235813213455") {
      
      echo "Credenziali corrette ";
      echo "<a href='home.php'>Vai...</a>"; //cambia
      }
   else {
   
   echo "RIFIUTATO. ";
   echo "<a href='accesso.php'>Riprova</a>";
   }
 
   ?>
    
    
</body>
</html>
