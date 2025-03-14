<?php
session_start();
function auth_middleware() {
    if (! check_if_signed_in())
        header('Location: signin.php');
}
function check_if_signed_in(): bool {
    return isset($_SESSION['auth']);
}
function _sign_in(): ?string {
    if ($_SERVER['REQUEST_METHOD'] != 'POST') {
        http_response_code(400);
        return 'Invalid request.';
    }
    $mysqli = new mysqli('localhost', 'lab_user', 'hello123', 'airline_db');
    if ($mysqli->connect_errno) {
        http_response_code(500);
        return 'Connection error: '.$mysqli->connect_error;
    }
    $username = $_POST['email'];
    $password = $_POST['password'];
    $stt = $mysqli->prepare('SELECT * FROM users WHERE email = ? AND password = ?');
    $stt->bind_param('ss', $username, $password);
    if (! $stt->execute()) {
        http_response_code(500);
        return 'Failed to login due to internal error.';
    }
    $res = $stt->get_result();
    $stt->close();
    if ($res->num_rows != 1) {
        http_response_code(403);
        return 'Invalid credentials.';
    }
    $_SESSION['auth'] = $res->fetch_assoc()['userid'];
    $mysqli->close();
    return null;
}
function sign_in(): bool {
    $error_msg = _sign_in();
    if ($error_msg == null) {
        return true;
    }

    echo <<<EOF
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="styles.css" rel="stylesheet">
        <title>Airly | Login error</title>
    </head>
    <body>
        <main>
            <div class="login-wrapper">
                <div class="login-container">
                    <div>
                        <div class="logo">Airly</div>
                        <div class="cta">Sign in.</div>
                    </div>
                    <div class="login-err">
                        <?php echo $error_msg; ?>
                        <div>
                            <a href="index.php" class="btn">Go back</a>
                        </div>
                    </div>
                </div>
            </div>
        </main>
    </body>
    </html>
    EOF;
    return false;
}
function sign_out() {
    session_destroy();
    header("Location: index.php");
}
?>
