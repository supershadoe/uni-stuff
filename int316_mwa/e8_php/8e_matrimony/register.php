<?php
    if (isset($_COOKIE['auth'], $_COOKIE['data']) && $_COOKIE['auth'] == 'done') {
        header("Location: ./success.php");
    } elseif ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (array_key_exists("email", $_POST)) {
            $data = array(
                "email" => $_POST['email'],
                "name" => $_POST['name'],
                "phno" => $_POST['phno'],
                "gender" => $_POST['gender'],
                "dob" => $_POST['dob'],
                "tongue" => $_POST['tongue'],
                'religion' => $_POST['religion'],
            );
            setcookie('auth', 'done', time() + 3600, '/');
            setcookie('data', json_encode($data), time() + 3600, '/');
            header("Location: "."./success.php");
        }
    }
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XYZ Matrimony: Register</title>
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
        <div class="big">Sign up.</div>
        <form method="post" action="">
            <div class="form">
                <div>
                    <label for="email">e-mail ID</label>
                    <input id="email" name="email" type="email" placeholder="john.doe@example.com" required />
                </div>
                <div>
                    <label for="pwd">Password</label>
                    <input id="pwd" name="pwd" type="password" required />
                </div>
                <div>
                    <label for="name">Name</label>
                    <input id="name" name="name" type="text" placeholder="John Doe" required />
                </div>
                <div>
                    <label for="phno">Phone number</label>
                    <input id="phno" name="phno" type="tel" placeholder="+1 (653) 343-343" required />
                </div>
                <div>
                    <span>Gender</span>
                    <input id="male-gender" name="gender" value="male" type="radio" checked />
                    <label for="male-gender">Male</label>
                    <input id="female-gender" name="gender" value="female" type="radio" />
                    <label for="female-gender">Female</label>
                    <input id="other-gender" name="gender" value="other" type="radio" />
                    <label for="other-gender">Other</label>
                </div>
                <div>
                    <label for="dob">Date of Birth</label>
                    <input id="dob" name="dob" type="date" required />
                </div>
                <div>
                    <label for="tongue">Mother tongue</label>
                    <input id="tongue" name="tongue" type="text" required />
                </div>
                <div>
                    <label for="religion">Religion</label>
                    <select id="religion" name="religion">
                        <option value="hindu">Hindu</option>
                        <option value="christian">Christian</option>
                        <option value="muslim">Muslim</option>
                        <option value="jewish">Jewish</option>
                        <option value="sikh">Sikh</option>
                        <option value="buddhist">Buddhist</option>
                        <option value="other">Other</option>
                    </select>
                </div>
                <div>
                    <input type="submit" />&emsp;<input type="reset" />
                </div>
            </div>
        </form>
    </main>

    <?php include_once("layout/footer.php") ?>
</body>

</html>
