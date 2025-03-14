<?php
    $login_failed = false;
    $reset_sent = false;
    if (isset($_COOKIE['auth'], $_COOKIE['data']) && $_COOKIE['auth'] == 'done') {
        header("Location: ./success.php");
    } elseif ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (array_key_exists("uname", $_POST)
            && $_POST["uname"] == "admin@mymatrimony.com"
            && $_POST["pwd"] == "password123"
        ) {
            $data = array(
                "email" => $_POST['uname'],
                "name" => "Admin",
                "phno" => "90000 00000",
                "gender" => "Male",
                "dob" => "01-01-1970",
                "tongue" => "English",
                'religion' => "Other",
            );
            setcookie('auth', 'done', time() + 3600, '/');
            setcookie('data', json_encode($data), time() + 3600, '/');
            header("Location: ./success.php");
        } else if (array_key_exists("reset_mail", $_POST)) {
            $reset_sent = true;
        } else {
            $login_failed = true;
        }
    }
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XYZ Matrimony: Login</title>
    <link href="styles.css" rel="stylesheet">
    <style>
        #forms {
            display: flex;
            flex-direction: row;
            justify-content: center;
            gap: 32px;
        }

        .form div {
            padding: 10px;
            display: flex;
            gap: 8px;
        }
    </style>
</head>

<body>
    <?php include_once("layout/nav.php") ?>

    <main>
        <h3>Login to access our services.</h3>
        <form method="post" action="">
            <div class="form">
                <div>
                    <label for="uname">Username</label>
                    <input id="uname" name="uname" type="text" placeholder="example@example.com" />
                </div>
                <div>
                    <label for="pwd">Password</label>
                    <input id="pwd" name="pwd" type="password" />
                </div>
                <div>
                    <a href="./login.php?forgot=true">Forgot password?</a>&emsp;
                    <a href="./register.php">Register</a>
                </div>
                <div>
                    <input type="Submit" value="Sign in" />
                </div>
            </div>
        </form>

        <?php
            if ($login_failed) {
                echo "Failed to login.";
            }
            if ($reset_sent) {
                echo "Sent reset mail.";
            }
            if (array_key_exists("forgot", $_GET)
                && $_GET["forgot"] == "true") {
        ?>
                <form action="" method="post">
                    <div class="form">
                        <div>
                            <label for="reset-mail">Reset mail</label>
                            <input id="reset-mail" name="reset_mail" type="email" />
                        </div>
                        <div>
                            <input type="Submit" value="Send mail" />
                        </div>
                    </div>
                </form>
         <?php } ?>

    </main>

    <?php include_once("layout/footer.php") ?>
</body>

</html>
