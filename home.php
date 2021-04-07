<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" type="text/css" href="style.css?ts=<time()?>&quot">
    <title><?php echo "Home"; ?></title>
</head>
<body>
    <p class="Titolo">TRACCIAMENTO GPS</p>
    
    <div class="topnav">
        <a class="active" href="home.php">Home</a>
        <a href="database.php">Database</a>
        <a href="galleria.php">Galleria</a>
        <a href="mappa.php">Mappa</a>
    </div>
    
    </br>

    Ora di ingresso: <?php echo date('H:i'); ?><br> Data: <?php echo date('d/m/y'); ?> <br /><br />  
    
    <?php
            
            $output = shell_exec('/home/pi/c/helloWorld'); 
            echo " Risultato lancio dell'eseguibile helloWorld: <pre>$output</pre>"; 
            ?>
    
</body>
</html>
