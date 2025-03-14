<?php
    $error_msg = '';
    session_start();
    if (! isset($_SESSION['username'])) {
        header('Location: index.php');
    }
    $mysqli = new mysqli('localhost', 'lab_user', 'hello123', 'ResMgr');
    if ($mysqli->connect_errno) {
        $error_msg = 'Failed to connect to database.';
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="styles.css" rel="stylesheet">
    <title>Resmgr</title>
</head>
<body>
    <nav>
        <div class="logo">Resmgr</div>
        <div class="vert">
            Logged in as <?php echo $_SESSION['username']; ?>
            <a href="logout.php">Sign out</a>
        </div>
    </nav>
    <main>
        <div class="page-wrapper">
            <div class="tabs-wrapper">
                <div class="tabs">
                    <a class="tab-item" href="dashboard.php?type=allocations">Allocations</a>
                    <a class="tab-item" href="dashboard.php?type=projects">Projects</a>
                </div>
            </div>
            <?php if ($error_msg) { ?>
            <div>
                <?php echo $error_msg ?>
            </div>
            <?php } else { ?>
            <div class="project-container">
                <div>
                </div>
                <form class="login-form" method="post" action="login.php">
                    <label for="username">Username</label>
                    <input type="text" id="username" name="username" required>
                    <label for="password">Password</label>
                    <input type="password" id="password" name="password" required>
                    <div>
                        <input type="submit" value="SIGN IN" class="btn">
                    </div>
                </form>
            </div>
            <?php } ?>
            <div class="footer">
                Powered by nosleep
            </div>
        </div>
    </main>
</body>
</html>