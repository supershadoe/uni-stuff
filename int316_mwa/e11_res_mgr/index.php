<?php
    session_start();
    if (isset($_SESSION['username'])) {
        header('Location: dashboard.php');
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="styles.css" rel="stylesheet">
    <title>Login | Resmgr</title>
</head>
<body>
    <main>
        <div class="login-wrapper">
            <div class="login-container">
                <div>
                    <div class="logo">Resmgr</div>
                    <div class="cta">Sign in.</div>
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
        </div>
    </main>
</body>
</html>