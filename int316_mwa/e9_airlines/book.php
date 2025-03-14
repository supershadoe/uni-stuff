<?php
    include_once('utils/auth.php');
    auth_middleware();
    $mysqli = new mysqli('localhost', 'lab_user', 'hello123', 'airline_db');
    if ($mysqli->connect_errno)
        die('Connection error: '.$mysqli->connect_error);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Airly | Book tickets</title>
    <link href="styles.css" rel="stylesheet">
</head>
<body>
    <nav>
        <div class="logo">Airly</div>
        <div class="links">
            <div><a href="index.php">Home</a></div>
            <div><a href="book.php">Book tickets</a></div>
            <div><a href="signout.php">Sign out</a></div>
        </div>
    </nav>
    <div class="flights">
        <?php
            $res = $mysqli->query('SELECT source, dest, TIME(dep_time) AS dep_time, TIME(arr_time) AS arr_time, TIMEDIFF(arr_time, dep_time) AS duration FROM flights');
            if ($res->num_rows <= 0) {
        ?>
            <div>No flights found.</div>
        <?php
            } else {
                for ($i = 0; $i < $res->num_rows; $i++) {
                    $row = $res->fetch_assoc();
        ?>
            <div class="flight">
                <div>
                    <div><?php echo $row['source']; ?> -> <?php echo $row['dest']; ?></div>
                    <div>Depature time: <?php echo $row['dep_time']; ?></div>
                    <div>Reaches <?php echo $row['dest']; ?> by <?php echo $row['arr_time']; ?></div>
                    <div>Duration: <?php echo $row['duration']; ?></div>
                </div>
                <div>
                    <a href="#" class="btn btn-orange">BOOK</a>
                </div>
            </div>
        <?php
                }
            }
        ?>
    </div>
</body>
</html>
