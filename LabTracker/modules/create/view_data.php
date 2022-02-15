<?php
    /**
     * Copyright (C) David Guijosa Infante - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by David Guijosa Infante <davidgin641@gmail.com>, 8/11/21 1:27 PM
     */
?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>
</head>
    <?php if( $GLOBALS['app']->users->isLoggedIn() ){ ?>
<body id="<?= $data['_id']?>">
    <?php include CORE_PATH . 'assets/inc/header.php';?>
    <section id="main">
        <div class="aligncenter">
            <div id="kioskFormArea">
                <form id="CreateAction" name = 'file' method="post" action="create/data" enctype="multipart/form-data">
                    <div class="classcreate">
                        <label>
                        <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="CreateOneCourse" type="button" value="Create One Course" />' ?> 
                        <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="CreateCourses" type="button" value="Create Courses"/>' ?> 
                        <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="CreateTerm" type="button" value="Create Term"/>' ?> 
                        <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="SetTerm" type="button" value="Set Term"/>' ?> 
                        </label>
                    </div>
                    
                    <div class="results"></div>
                    <div class="filters"></div>
                    <div class="adminphase2 none"></div>
                    <div class="adminphase2pages"></div>
                </form>
                
            </div>
        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>
 <?php } ?>
</html>