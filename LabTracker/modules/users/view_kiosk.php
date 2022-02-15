<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 6/17/21 4:54 PM
     */

?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles();?>
</head>

<body id="<?= $data['_id']?>">
    <?php include CORE_PATH . 'assets/inc/header.php';?>
    <section id="main">
        <div class="aligncenter">
            <div class="kioskLogo">
                <img src="<?=CORE_URL?>assets/img/timer.png" width="127">
                <p>Lab Tracker</p>
            </div>
            
            <div id="kioskFormArea">
                <?php
                    if( $data['open'] || $GLOBALS['app']->users->isLoggedIn() ){
                ?>
                <form id="LogIn" method="post" action="users/kiosk">
                    <input type="hidden" name="phase" value="1" />
                    <div class="errors"></div>
                    <div class="phase1">
                        <label>
                            <div class="flexWrap sidInput">
                                <input class="flex sid" type="text" name="sid" placeholder="Student Id" />
                                <div class="progress-line" style="display: none"></div>
                            </div>
                            
                        </label>
                        <div class="Register">
                            <div class="log"></div>
                            <br><a id="AddCourse" href="">Add Course</a><br> Or <a id="Register" href="">Register</a>
                        </div>
                        <div class="margin20Top">
                            <a href="<?= CORE_URL ?>assets/misc/How-to.pdf">How to use Lab Tracker</a>
                        </div>
                    </div>
                    <div class="phase2 none">
                        <p>Choice a course for lab</p>
                        <input class="sid" type="hidden" name="sid">
                        <div class="courses"></div>
                        <input type="submit" value="Start">
                        <input type="button" id='cancel' value="Cancel">
                    </div>
                </form>
                <div class="result"></div>
                <?php } else { ?>
                    <p>The lab is currently closed come back during open hours</p>
                <?php } ?>
            </div>

        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>

</html>