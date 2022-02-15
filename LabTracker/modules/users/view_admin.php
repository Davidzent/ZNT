<?php
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
            <div id="adminFormArea">
                <form id="AdminAction" method="post" action="users/admin">
                    <input type="hidden" name="option" value="0"/>
                    <input type="hidden" name="phase" value="1"/>
                    <div class="errors"></div>
                    <div class="adminphase1">
                        <label>
                            <?php if( Core::hasRole( users::VERIFY ) || Core::hasRole( users::ADMIN ) ) echo '<input id="Verify" type="submit" value="Verify" />' ?>
                            <?php if( Core::hasRole( users::VERIFY ) || Core::hasRole( users::ADMIN ) ) echo '<input id="VAS" type="submit" value="View Active Students"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditReports" type="submit" value="Edit Completed Attendance"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditIncompleteReports" type="submit" value="Edit Incomplete Attendance"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditSection" type="submit" value="Edit Classes"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditStudents" type="submit" value="Edit Students"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditStudentClasses" type="submit" value="Edit Student Classes"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditUsers" type="submit" value="Edit Staff"/>' ?>
                            <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="EditTerm" type="submit" value="Edit Terms"/>' ?>
                        </label>
                    </div>
                    <div class="filters"></div>
                    <div class="adminphase2 none"></div>
                    <div class="adminphase2pages"></div>
                </form>

                <div class="result"></div>

            </div>

        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>
 <?php } ?>
</html>