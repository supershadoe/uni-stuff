<?php
    include_once('utils/auth.php');
    $logged_in = check_if_signed_in();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Airly | Book flights easily</title>
    <link href="styles.css" rel="stylesheet">
</head>
<body>
    <nav>
        <div class="logo">Airly</div>
        <div class="links">
            <div><a href="index.php">Home</a></div>
            <div><a href="book.php">Book tickets</a></div>
            <?php if ($logged_in) { ?>
            <div><a href="signout.php">Sign out</a></div>
            <?php } else { ?>
            <div><a href="signin.php">Sign in</a></div>
            <?php } ?>
        </div>
    </nav>
    <div class="hero">
        <div class="hero-text">
            <div>
                <div class="text-3xl">
                    AIRLY
                </div>
                <div class="text-xl">
                    Book flights fast and easily.
                </div>
            </div>
            <div>
                <a href="book.php" class="btn btn-orange">
                    BOOK TICKETS
                </a>
            </div>
        </div>
        <div>
            <img src="assets/icons8-airplane-take-off-96.png" height="128">
        </div>
    </div>
</body>
</html>
