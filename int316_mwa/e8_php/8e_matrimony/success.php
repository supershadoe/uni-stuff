<?php
    $data = array();
    if ((! isset($_COOKIE['auth'], $_COOKIE['data'])) || $_COOKIE['auth'] != 'done') {
        header("Location: ./login.php");
    } else {
        $data = json_decode($_COOKIE['data'], true);
    }
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XYZ Matrimony: Home page</title>
    <link href="styles.css" rel="stylesheet">
    <style>
        .details {
            margin: 16px 0;
        }
    </style>
</head>

<body>
    <?php include_once("layout/nav.php") ?>

    <main>
        <div class="big">Successfully logged in!</div>
        <div class="details">
            <table>
                <tr>
                    <td>Name</td>
                    <td><?php echo $data['name'] ?></td>
                </tr>
                <tr>
                    <td>E-mail ID</td>
                    <td><?php echo $data['email'] ?></td>
                </tr>
                <tr>
                    <td>Phone num</td>
                    <td><?php echo $data['phno'] ?></td>
                </tr>
                <tr>
                    <td>Gender</td>
                    <td><?php echo $data['gender'] ?></td>
                </tr>
                <tr>
                    <td>DOB</td>
                    <td><?php echo $data['dob'] ?></td>
                </tr>
                <tr>
                    <td>Mother tongue</td>
                    <td><?php echo $data['tongue'] ?></td>
                </tr>
                <tr>
                    <td>Religion</td>
                    <td><?php echo $data['religion'] ?></td>
                </tr>
            </table>
        </div>
        <a href="./logout.php">Log out</a>
    </main>

    <?php include_once("layout/footer.php") ?>
</body>

</html>
