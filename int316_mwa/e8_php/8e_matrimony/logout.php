<?php
    unset($_COOKIE['auth'], $_COOKIE['data']);
    setcookie('auth', '', 1, '/');
    setcookie('data', '', 1, '/');
    header("Location: ./index.php");
?>