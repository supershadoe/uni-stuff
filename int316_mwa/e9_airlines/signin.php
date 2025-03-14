<?php
    include_once('utils/auth.php');
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        if (sign_in()) {
            header('Location: book.php');
        }
    } elseif (check_if_signed_in()) {
        header('Location: book.php');
    } else {
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Airly | Sign in</title>
    <link href="styles.css" rel="stylesheet">
</head>
<body class="signin">
    <main>
        <div class="login-wrapper">
            <div class="login-container">
                <div>
                    <div class="logo">Airly</div>
                    <div class="cta">Sign in.</div>
                </div>
                <form class="login-form" method="post" action="">
                    <label for="email">e-mail</label>
                    <input type="email" id="email" name="email" required>
                    <label for="password">Password</label>
                    <input type="password" id="password" name="password" required>
                    <div>
                        <input type="submit" value="SIGN IN" class="btn btn-blue">
                    </div>
                </form>
            </div>
        </div>
    </main>
</body>
</html>
<?php } ?>
