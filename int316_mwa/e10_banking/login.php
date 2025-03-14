<?php
    session_start();
    $failed_login = FALSE;
    if (isset($_SESSION["auth"])) {
        header("Location: dashboard.php");
    } else {
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $email = $_POST["email"];
            $pwd = $_POST["pwd"];
            $conn = new mysqli("localhost", "lab_user", "hello123", "banking_system");
            if (! $conn) {
                die("Failed to connect to database.");
            }
            $res = $conn->query("SELECT customer_id FROM customers WHERE email = '$email' AND pwd = '$pwd'");
            if ($res->num_rows > 0) {
                $row = $res->fetch_assoc();
                $_SESSION["auth"] = $row["customer_id"];
                header("Location: dashboard.php");
            } else {
                $failed_login = TRUE;
            }
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login | XYZ Bank</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <nav>
        <div>
            XYZ BANK
        </div>
        <div></div>
    </nav>
    <main>
        <div class="text-2xl">
            Login.
        </div>
        <form action="" method="post">
            <label for="email">E-mail</label>
            <br><br>
            <input id="email" name="email" type="email" required />
            <br><br>
            <label for="pwd">Password</label>
            <br><br>
            <input id="pwd" name="pwd" type="password" required />
            <br><br>
            <input type="submit" class="btn bg-blue text-white" value="Sign in" />
            <?php if ($failed_login) { ?>
            <div class="error">Failed to login; check your mail id and password</div>
            <?php } ?>
        </form>
</body>
</html>
