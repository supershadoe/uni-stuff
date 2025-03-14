<?php
    session_start();
    function login() {
        if ($_SERVER['REQUEST_METHOD'] != 'POST') {
            http_response_code(400);
            return 'Invalid request.';
        }
        $mysqli = new mysqli('localhost', 'lab_user', 'hello123', 'ResMgr');
        if ($mysqli->connect_errno) {
            http_response_code(500);
            return 'Connection error: '.$mysqli->connect_error;
        }
        $username = $_POST['username'];
        $password = $_POST['password'];
        $stt = $mysqli->prepare('SELECT * FROM Users WHERE Username = ? AND Pwd = ?');
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
        $_SESSION['username'] = $res->fetch_assoc()['Username'];
        $mysqli->close();
        header('Location: dashboard.php');
    }
    $error_msg = login();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="styles.css" rel="stylesheet">
    <title>Login error | Resmgr</title>
</head>
<body>
    <main>
        <div class="login-wrapper">
            <div class="login-container">
                <div>
                    <div class="logo">Resmgr</div>
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