<!DOCTYPE html>

<html>
<head>
    <link rel="stylesheet" type="text/css" href="style.css?ts=<time()?>&quot">
    <title>Accesso</title>
</head>
<body>
    <p class="Titolo">
        Pagina di accesso al Raspberry di Alessandro
    </p>

    Ora di ingresso: <?php echo date('H:i'); ?><br> Data: <?php echo date('d/m/y'); ?> <br /><br />
    
    <form action="controlloCredenziali.php" method="post" name="accesso" >    

    user:  <input type="text" name="user" id="user" />
    psw :  <input type="password" name="psw" id="psw" />
           <button type="submit">accedi</button>
          
    </form>

</body>
</html>
