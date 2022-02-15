<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 6/17/21 4:52 PM
     */

    class users extends module {
        const KIOSK = 1;
        const ADMIN = 2;
        const REPORTS = 3;
        const VERIFY = 4;

        public function fetch( $options = array() ) {
            $options = Core::getOptions( [
                'table' => '',
                'fields' => '*',
                'where' => '',
                'params' => array(),
                'page' => 1,
                'limit' => -1,
                'table' => -1,
                'order' => '',
                'roles' => false
            ], $options );

            $getOptions = [
                'where' => $options['where'],
                'params' => $options['params'],
                'fields' => $options['fields'],
                'order' => $options['order']
                // 'table' => $options['table']
            ];
            //allow for pagination offset 0,10 kind of thing
            if( $options['limit'] != -1 ){
                $offset = ( $options['page'] - 1 ) * $options['limit'];
                $getOptions['limit'] = $offset . ',' . $options['limit'];
            }

            if( $options['table'] != -1){
                $getOptions['table'] = $options['table'];
            }

            $users = $this->model->get( $getOptions );
            if( $options['roles'] ) {
                foreach ( $users as $key => $item ) {
                    $users[$key]['roles'] = $this->model->getRoles( $item['id'] );
                }
            }
            return $users;
        }

        public function fetchOne( $options = [] ){
            $options = Core::getOptions( array(
                'where' => '',
                'params' => array(),
                'id' => -1,
                'term' => -1,
                'email' => '',
                'fields' => 'users.*',
                'roles' => false,
                'details' => false,
            ), $options );

            if ( $options['id'] != -1 ) {
                $options['where'] = 'users.id=?';
                array_push( $options['params'], $options['id'] );
            } else if( !empty( $options['email'] ) ){
                $options['where'] = 'email=?';
                array_push( $options['params'], $options['email'] );
            }else if( $options['term'] != -1 ) {
                $options['where'] = 'term=?';
                array_push( $options['params'], $options['term'] );
            }
            if(isset($options['table'])){
                $user = $this->model->getOne( [
                    'where' => $options['where'],
                    'params' => $options['params'],
                    'fields' => 'term',
                    'table' => $options['table']
                ] );
            }
            else {
                $user = $this->model->getOne( [
                'where' => $options['where'],
                'params' => $options['params'],
                'fields' => $options['fields'],
                ] );
            } 
            if( $options['roles'] ){
                $user['roles'] = $this->model->getRoles( $user['id'] );
            }

            return $user;
        }

        public function kiosk() {
            if ( isset( $_POST[ 'sid' ] ) ) {
                //if is making a post on the kiosk form
                $_POST = Security::sanitize( $_POST ); //must be done with dealing
                $this->app->loadModule( 'students' );
                //check sid
                $data = $this->app->students->studentEntered( $_POST[ 'sid' ] );
                echo $data;

            } else if ( isset( $_POST[ 'Fname' ] ) && isset( $_POST[ 'Lname' ] ) && isset( $_POST[ 'StudentID' ])) {
                $_POST = Security::sanitize( $_POST );
                $this->app->loadModule( 'students' );
                //Register Student
                $data = $this->app->students->studentRegister( $_POST[ 'Fname' ], $_POST[ 'Lname' ], $_POST[ 'StudentID' ], $_POST[ 'section' ] );
                echo $data;

            } else if( isset($_POST['StudentID'])&&isset($_POST['Section'])){
                $_POST = Security::sanitize( $_POST );
                $this->app->loadModule( 'students' );

                $data = $this->app->students->AddCourse($_POST['StudentID'],$_POST['Section']);

                echo $data;
            }
            else {
                //no for data present the page instead

                $this->loadView( "kiosk", ['open' => $this->isLabOpen() ] );
            }
        }

        /**
         * login a user from the form. if no data posted displays the form
         */
        public function login(){
            //if has form data
            if( !isset( $_POST['email'] ) ){
                $this->loadView( "login" );
            } else {
                $_POST = Security::sanitize( $_POST );
                $userExists = $this->fetchOne( ['email' => $_POST['email'], 'roles' => true ] );
                if( $userExists === false ){
                    //user is not in the system
                    //TODO recovery system
                    Ajax::errorResponse( "Password or email is incorrect. Click TODO if you have forgotten your password.");
                } else {
                    $pass = Security::hashPassword( $_POST['password'], $_POST['email'] );
                    if( $userExists['password'] == $pass ){
                        //login success
                        //TODO ip history audit log
                        //check active and !banned
                        if( $userExists['active'] == 1 && $userExists['banned'] == 0 ){
                            setcookie( "session_expires", time(), time() + ( 10 * Time::MINUTE ), '/' );
                            setcookie( "session_started", Core::opt( $_COOKIE['session_started'], time() ), time() + ( 10 * Time::MINUTE ), '/' );
                            $_SESSION['session']['started'] = Core::opt( $_SESSION['session']['started'], time() );
                            $_SESSION['session']['expires'] = time() + ( 10 * Time::MINUTE ); //session set for 10 minutes
                            $_SESSION['session']['email'] = $userExists['email'];
                            $_SESSION['session']['name'] = $userExists['fname'] . ' ' . $userExists['lname'];
                            $_SESSION['session']['id'] = $userExists['id'];
                            $_SESSION['session']['roles'] = $userExists['roles']['ids'];

                            $output = [];
                            $output['msg'] = "Logged in successfully";
                            $output['action'] = 'redirect';
                            if( $userExists['changePassword'] ){
                                $output['href'] = CORE_URL . 'users/changePassword';
                            } else {
                                $output['href'] = CORE_URL;
                            }
                            Ajax::successResponse( $output );
                        } else if ( $userExists['active'] != 1 ){
                            Ajax::errorResponse( "Your account has been deactivated. Contact an administrator to re-activate your account." );
                        } else if( $userExists['banned'] == 1 ){
                            Ajax::errorResponse( "Your account has been banned. Contact an administrator if you feel this was an error.");
                        }
                    } else {
                        //login failure
                        Ajax::errorResponse( "Password or email is incorrect. Click TODO if you have forgotten your password.");
                    }
                }
            }
        }


        /**
         * check if a user is logged in
         * @param bool $refresh
         * @return bool
         */
        public function isLoggedIn( $refresh = true ){
            if ( isset( $_SESSION['session'] ) ) {
                //if expired and timeout is enabled log them out
                if( $_SESSION['session']['expires'] <= time() && !NO_TIMEOUT ){
                    $this->logout();
                    return false;
                } else {
                    if( $refresh ){
                        setcookie( "session_expires", time(), time() + ( 15 * Time::MINUTE ), '/' );
                        $_SESSION['session']['expires'] = time() + ( 15 * Time::MINUTE ); //session set for 10 minutes
                    }
                    return true;
                }
            }
        }

        /**
         * if logged return true if not redirect user to a page. usually the login page
         * @param string $ref where to put them if after logging in
         * @param bool $refresh refresh their session
         * @return bool
         */
        public function orRedir( $ref = '', $refresh = true){
            if ( $this->isLoggedIn( $refresh) ) {
                return true;
            } else {
                $s = 'users/login';
                if( empty( $ref ) ){
                    Core::phpRedirect( $s );
                } else {
                    Core::phpRedirect( "$s?ref=$ref" );
                }
            }
        }

        /**
         * logout of the system by clearing the cookies and session vars
         */
        public function logout(){
            if( isset( $_SESSION['session'] ) ) {
                unset( $_SESSION[ 'session' ] );
                if ( isset( $_COOKIE[ 'session_expires' ] ) ) {
                    unset( $_COOKIE[ 'session_expires' ] );
                    setcookie( 'session_expires', null, -1, '/' );
                }
                if ( isset( $_COOKIE[ 'session_started' ] ) ) {
                    unset( $_COOKIE[ 'session_started' ] );
                    setcookie( 'session_started', null, -1, '/' );
                }
            }
            Core::phpRedirect( "home" );
        }

        /**
         * change user password
         * currently there is no link to this from webpage
         */
        public function changePassword(){
            //if not logged in make them
            if( $this->orRedir( 'users/changePassword') ) {
                if( !isset( $_POST['password'] ) ){
                    //not data submit show html
                    $this->loadView( 'changePassword' );
                } else{
                    //data submitted preform action
                    $_POST = Security::sanitize( $_POST );
                    $userExists = $this->fetchOne( ['id' => Core::getUser() ] );
                    if( $userExists === false ){
                        //um wtf is this case logged in but no user. should never happen
                        $this->app->logs->error( "change password on user but no users exists", logs::PHP_FATAL );
                    } else {
                        //check the old password is right
                        if( $userExists['password'] == Security::hashPassword( $_POST['password'], $userExists['email'] ) ){
                            //hash new pass
                            $pass = Security::hashPassword( $_POST['newPassword'], $userExists['email'] );
                            $updated = $this->model->update([
                                'id' => $userExists['id'],
                                'update' => 'password=?,changePassword=?',
                                'params' => [$pass, 0]
                            ]);
                            if( $updated ){
                                Ajax::successResponse([
                                    'action' => 'redirect',
                                    'href' => $_SESSION['lastPage']
                                ], "Changed password Successfully");
                            } else {
                                $this->app->logs->error( "error updating password in users/changePassword", logs::PHP_WARNING );
                                Ajax::errorResponse( 'An error occurred changing your password.');
                            }
                        } else {
                            //wrong password
                            Ajax::errorResponse( 'Old password was wrong');
                        }
                    }
                }
            }
        }

        public function admin() {
            //check is logged in
            if( !$this->orRedir( 'users/admin' ) ) return;
            if(isset($_POST['option'])){
                $_POST = Security::sanitize( $_POST );
                $this->app->loadModule( 'students' );
                //list of non-validated students
                if($_POST['option']==1&&$_POST['phase']==1 && Core::hasRole( users::VERIFY )){
                    $data = $this->app->students->studentNotVerified();
                    echo $data;
                }
                //validate students have said course
                else if($_POST['option']==1&&$_POST['phase']==2&&isset($_POST['ValidatedStudents'] ) && Core::hasRole( users::VERIFY ) ){
                    $data = $this->app->students->ValidateStudents($_POST['ValidatedStudents']);
                    echo $data;
                }
                //see active students
                else if($_POST['option']==2&&$_POST['phase']==1 && Core::hasRole( users::VERIFY ) ){
                    $data = $this->app->students->ActiveStudents();
                    echo $data;
                }
                //TODO is this a verifier role? hmm maybe a ted question
                //logout students
                else if($_POST['option']==2&&$_POST['phase']==2&&isset($_POST['LogoutStudents']) && Core::hasRole( users::VERIFY ) ){
                    $data = $this->app->students->LogoutStudents($_POST['LogoutStudents']);
                    echo $data;
                }
                //edit time logs right?
                else if($_POST['option']==3&&$_POST['phase']==1 && Core::hasRole( users::ADMIN )){
                    $data = $this->app->students->StudentsTimeLogs(true,false); //false for complete true for incomplete
                    echo $data;
                }
                else if($_POST['option']==3&&$_POST['phase']==2&&(isset($_POST['EditReportsStudents'])||isset($_POST['RemoveStudents'])) && Core::hasRole( users::ADMIN ) ){
                    if($_POST['EditReportsStudents']==null){
                        $_POST['EditReportsStudents']="";
                    }
                    if($_POST['RemoveStudents']==null){
                        $_POST['RemoveStudents']="";
                    }
                    $data = $this->app->students->EditStudentsLogs($_POST['EditReportsStudents'],$_POST['RemoveStudents'],true);
                    echo $data;
                }
                //list sections
                else if($_POST['option']==4&&$_POST['phase']==1 && Core::hasRole( users::ADMIN ) ){
                    $data = $this->app->students->Sections("");
                    echo $data;
                }
                //edit sections
                else if($_POST['option']==4&&$_POST['phase']==2&&(isset($_POST['EditSection'])||isset($_POST['RemoveSection'])) && Core::hasRole( users::ADMIN ) ){
                    if($_POST['EditSection']==null){
                        $_POST['EditSection']="";
                    }
                    if($_POST['RemoveSection']==null){
                        $_POST['RemoveSection']="";
                    }

                    $data = $this->app->students->EditSections($_POST['EditSection'],$_POST['RemoveSection']);
                    echo $data;
                }
                //list incomplete
                else if($_POST['option']==5 && $_POST['phase']==1 && Core::hasRole( users::ADMIN )){
                    $data = $this->app->students->StudentsTimeLogs(false,false);
                    echo $data;
                }
                //edit incomplete students records
                else if($_POST['option']==5&&$_POST['phase']==2&&(isset($_POST['EditReportsStudents'])||isset($_POST['RemoveStudents'])) && Core::hasRole( users::ADMIN ) ){
                    $_POST = Security::sanitize( $_POST );
                    $this->app->loadModule( 'students' );
                    if($_POST['EditReportsStudents']==null){
                        $_POST['EditReportsStudents']="";
                    }
                    if($_POST['RemoveStudents']==null){
                        $_POST['RemoveStudents']="";
                    }
                    $data = $this->app->students->EditStudentsLogs($_POST['EditReportsStudents'],$_POST['RemoveStudents'],false);
                    echo $data;
                }
                //list students
                else if($_POST['option']==6&&$_POST['phase']==1 && Core::hasRole( users::ADMIN ) ){
                    $_POST = Security::sanitize( $_POST );
                    $this->app->loadModule( 'students' );
                    $data = $this->app->students->listing(false);
                    echo $data;
                }
                //edit students
                else if($_POST['option']==6&&$_POST['phase']==2&&(isset($_POST['EditStudent'])||isset($_POST['RemoveStudent'])) && Core::hasRole( users::ADMIN ) ){
                    $_POST = Security::sanitize( $_POST );
                    $this->app->loadModule( 'students' );
                    if($_POST['EditStudent']==null){
                        $_POST['EditStudent']="";
                    }
                    if($_POST['RemoveStudent']==null){
                        $_POST['RemoveStudent']="";
                    }
                    $data = $this->app->students->EditStudents($_POST['EditStudent'],$_POST['RemoveStudent'],false);
                    echo $data;
                }
                //list student courses
                else if($_POST['option']==7&&$_POST['phase']==1 && Core::hasRole( users::ADMIN ) ){
                    $_POST = Security::sanitize( $_POST );
                    $this->app->loadModule( 'students' );
                    $data = $this->app->students->StudentsClasses(false);
                    echo $data;
                }
                //edit student courses
                else if($_POST['option']==7&&$_POST['phase']==2&&(isset($_POST['EditStudentClass'])||isset($_POST['RemoveStudentClass'])) && Core::hasRole( users::ADMIN ) ){
                    $_POST = Security::sanitize( $_POST );
                    $this->app->loadModule( 'students' );
                    if($_POST['EditStudentClass']==null){
                        $_POST['EditStudentClass']="";
                    }
                    if($_POST['RemoveStudentClass']==null){
                        $_POST['RemoveStudentClass']="";
                    }
                    $data = $this->app->students->EditStudentsClasses($_POST['EditStudentClass'],$_POST['RemoveStudentClass'],false);
                    echo $data;
                }
                //list/edit users
                else if( $_POST['option'] == 8 && Core::hasRole( users::ADMIN ) ){ //edit the users table actions
                    if( $_POST['phase'] == 1 ) {
                        $this->listing();
                    } else {
                        if( isset( $_POST['edit'] ) || isset( $_POST['remove'] ) ){
                            //TODO fix this notice dont wanna see it in the logs
                            $this->edit( $_POST['edit'], $_POST['remove'] );
                        }
                    }
                }
                else if( $_POST['option'] == 9 && Core::hasRole( users::ADMIN ) ){ //edit the Terms table
                    if( $_POST['phase'] == 1 ) {
                        $data=$this->fetch(['table'=>'terms']);
                        $data = Ajax::response(['terms'=>$data], true, "The course was send succesfully.");
                    } else {
                        if( isset( $_POST['EditTerms'] ) ) {
                            $data = $this->editTerm( $_POST['EditTerms'] );
                        }
                    }
                    echo $data;
                }
            }
            else{
               $this->loadView( "admin" );
            }

        }

        /**
         * display a listing of the users in json only
         */
        private function listing( $msg = '' ){
            $users = $this->fetch([
                'fields' => 'email,fname,lname,id,active,banned',
                'limit' => 100
            ]);
            if( isset( $users ) ){
                Ajax::successResponse( $users, $msg);
            } else {
                if( empty( $msg ) )
                    $msg = "Failed to load page";
                Ajax::errorResponse( $msg );
            }
        }
        /**
         * edit/remove from the admin user table
         * @param array $edits
         * @param array $removes
         */
        private function editTerm( $edits){
            //assumes post was cleaned in users->admin
            $errors = "";
            if( $edits ){
                foreach ( $edits as $key => $item ) {
                    //get user
                    $term = $this->fetchOne( [ 'table'=>'terms','term' => $item ] );
                    if( $term !== false ) {
                        $pData = [
                            'startDate' => $_POST[ 'startdate' ][ $key ],
                            'endDate' => $_POST[ 'endtdate' ][ $key ]
                        ];

                        $options = [
                            'table' => 'terms',
                            'update' => 'startDate=?,endDate=?',
                            'where' => 'term=?',
                            'params' => [ $pData[ 'startDate' ], $pData[ 'endDate' ], $item ]
                        ];
                        $updated = $this->model->update( $options );
                        if ( $updated === false ) {
                            $errors .= 'Failed to edit: ' . $item . '<br/>';
                        }
                    } else {
                        $errors .= $item." doesn't exist<br/>";
                    }
                }
            }
            $data=$this->fetch(['table'=>'terms']);
            return $data = Ajax::response(['terms'=>$data,'errors'=>$errors], true, "The course was send succesfully.");
        }

        /**
         * edit/remove from the admin user table
         * @param array $edits
         * @param array $removes
         */
        private function edit( $edits, $removes ){
            //assumes post was cleaned in users->admin
            $errors = "";
            //Delete first
            if( $removes ){
                foreach ( $removes as $item ) {
                    $user = $this->model->deleteUser( $item );
                    if( $user === false ){
                        $errors .= "Error removing the user: $item <br/>";
                    }
                }
            }

            if( $edits ){
                foreach ( $edits as $key => $item ) {
                    //get user
                    $user = $this->fetchOne( [ 'id' => $item ] );
                    if( $user !== false ) {
                        $pData = [
                            'email' => $_POST[ 'email' ][ $key ],
                            'fname' => $_POST[ 'fname' ][ $key ],
                            'lname' => $_POST[ 'lname' ][ $key ]
                        ];

                        $options = [
                            'update' => 'email=?,fname=?,lname=?',
                            'where' => 'id=?',
                            'params' => [ $pData[ 'email' ], $pData[ 'fname' ], $pData[ 'lname' ], $item ]
                        ];
                        $updated = $this->model->update( $options );
                        if ( $updated === false ) {
                            $errors .= 'Failed to edit: ' . $pData[ 'email' ] . '<br/>';
                        }
                    } else {
                        $errors .= "${$pData[ 'email' ]} doesn't exist<br/>";
                    }
                }
            }

            $this->listing( "The Edit Was Successful" );
        }

        /**
         * Edit roles and show the edit roles html if no post is seen.
         * @param int $id
         */
        public function editRole( $id ){
            $_POST = Security::sanitize( $_POST );
            if( $this->isLoggedIn() && Core::hasRole( users::ADMIN )){
                $user = $this->fetchOne( ['id' => $id, 'roles' => true ]);
                $roles = $user['roles']['friendly'];

                if( isset( $_POST['active'] ) ){
                    //do the edit
                    //look for edits that need to happen
                    $actions = [
                        'add' => [],
                        'delete' => []
                    ];
                    foreach ( $_POST as $item ) {
                        if( $item['id'] == "banned" || $item['id'] == 'active' )
                            continue;
                        //if the value is in the list of roles currently
                        if( isset( $roles[ $item['id'] ] ) ){
                            //if they unchecked it mark it
                            if( !boolval( $item['checked'] ) ){
                                $actions['delete'][] = [$id, $item['id'] ];
                            }
                        } else {
                            if( boolval( $item['checked'] ) ){
                                $actions['add'][] = [$id, $item['id'] ];
                            }
                        }
                    }

                    //update the user table
                    $this->model->update([
                        'id' => (int)$id,
                        'update' => 'active=?,banned=?',
                        'params' => [
                            (int)$_POST['active']['checked'], (int)$_POST['banned']['checked']
                        ]
                    ]);

                    //edit the roles
                    //add new roles
                    foreach ( $actions['add'] as $item ) {
                        $this->model->addRole( $item[0], $item[1] );
                    }
                    //delete roles
                    //add new roles
                    foreach ( $actions['delete'] as $item ) {
                        $this->model->deleteRole( $item[0], $item[1] );
                    }

                    Ajax::successResponse( null, 'Saved' );

                } else {
                ?>
                <form>
                    <div>
                        <ul id="adminEditRoles">
                            <li>
                                <div>Roles</div>
                                <div>Has Access</div>
                            </li>
                            <li>
                                <div>
                                    <p>Kiosk</p>
                                </div>
                                <div><input name='kiosk' type='checkbox' value="<?= users::KIOSK?>" <?= ( ( isset( $roles[ users::KIOSK] ) ) ? ( 'checked ' ) : ( '' ) )?> /></div>
                            </li>
                            <li>
                                <div>
                                    <p>Reports</p>
                                </div>
                                <div><input name='reports' type='checkbox' value="<?= users::REPORTS?>" <?= ( ( isset( $roles[ users::REPORTS] ) ) ? ( 'checked ' ) : ( '' ) )?> /></div>
                            </li>
                            <li>
                                <div>
                                    <p>Verifier</p>
                                </div>
                                <div>
                                    <input name='verify' type='checkbox' value="<?= users::VERIFY?>" <?= ( ( isset( $roles[ users::VERIFY] ) ) ? ( 'checked ' ) : ( '' ) )?> />
                                </div>
                            </li>
                            <li>
                                <div>
                                    <p>Administrator</p>
                                </div>
                                <div><input name='admin' type='checkbox' value="<?= users::ADMIN?>" <?= ( ( isset( $roles[ users::ADMIN] ) ) ? ( 'checked ' ) : ( '' ) )?> /></div>
                            </li>
                        </ul>
                    </div>
                    <div class="margin10Top aligncenter">
                        <span>Current Status</span>
                        <input type="checkbox" name="active" value="active" <?= Core::getUser() == $user['id'] ? 'disabled' : '' ?> <?= ( ( ( $user['active'] ) ) ? ( 'checked ' ) : ( '' ) )?>/>Active
                        <input type="checkbox" name="banned" value="banned" <?= Core::getUser() == $user['id'] ? 'disabled' : '' ?> <?= ( ( ( $user['banned'] ) ) ? ( 'checked ' ) : ( '' ) )?>/>Banned
                    </div>
                </form>
                <?php
                }
            }
        }

        /**
         * create a user
         */
        public function create(){
            $_POST = Security::sanitize( $_POST );
            if ( isset( $_POST['email'] ) ) {
                //check email is not in user
                $exists = $this->fetchOne(['email' => $_POST['email'] ] );
                if( $exists === false ) {
                    $regexErrors = "";
                    //regex
                    if( !Regex::test( Regex::$EMAIL, $_POST['email'] ) )
                        $regexErrors .= "<p>Email must be a valid email</p>";
                    if( empty( $_POST['fname'] ) )
                        $regexErrors .= "<p>First name must be at least 1 character</p>";
                    if( empty( $_POST['lname'] ) )
                        $regexErrors .= "<p>Last name must be at least 1 character</p>";

                    if( !empty( $regexErrors ) ){
                        Ajax::errorResponse( $regexErrors);
                        return;
                    }

                    //hash salt
                    $_POST['password'] = Security::hashPassword( $_POST['password'], $_POST['email'] );
                    //insert
                    $inserted = $this->model->insertOne([
                        'fields' => 'email,fname,lname,password,ip,active,changePassword',
                        'params' => [
                            $_POST['email'],
                            $_POST['fname'],
                            $_POST['lname'],
                            $_POST['password'],
                            Core::getIp(),
                            (int)$_POST['active'],
                            1
                        ]
                    ]);

                    //add the roles
                    if( $inserted !== false ) {
                        if( $_POST['kiosk'] == '1' )
                            $this->model->addRole( $inserted, users::KIOSK );
                        if( $_POST['admin'] == '1' )
                            $this->model->addRole( $inserted, users::ADMIN );
                        if( $_POST['reports'] == '1' )
                            $this->model->addRole( $inserted, users::REPORTS );
                        if( $_POST['verify'] == '1' )
                            $this->model->addRole( $inserted, users::VERIFY );
                    }
                    Ajax::successResponse( [ 'i' => $inserted], 'Created successfully');
                } else {
                    Ajax::successResponse( null, 'User with that email already exists');
                }
            } else {
                ?>
                <form>
                    <div class="errors"></div>
                    <div class="margin5Bottom">
                        <label for="email">Email</label>
                        <input type="email" id="email" name="email" placeholder="Email" value="w@w.w" />
                    </div>
                    <div class="margin5Bottom">
                        <label for="fname">First Name</label>
                        <input type="text" id="fname" name="fname" placeholder="First Name" value="w" />
                    </div>
                    <div class="margin5Bottom">
                        <label for="lname">Last Name</label>
                        <input type="text" id="lname" name="lname" placeholder="Last Name" value="w" />
                    </div>
                    <div class="margin5Bottom">
                        <label for="password">Password (changed on login)</label>
                        <input type="text" id="password" name="password" placeholder="password" value="12345" />
                    </div>
                    <div>
                        <ul id="adminEditRoles">
                            <li>
                                <div>Roles</div>
                                <div>Has Access</div>
                            </li>
                            <li>
                                <div>
                                    <p>Kiosk</p>
                                </div>
                                <div><input name='kiosk' type='checkbox' value="<?= users::KIOSK?>"/></div>
                            </li>
                            <li>
                                <div>
                                    <p>Reports</p>
                                </div>
                                <div><input name='reports' type='checkbox' value="<?= users::REPORTS?>"/></div>
                            </li>
                            <li>
                                <div>
                                    <p>Verifier</p>
                                </div>
                                <div>
                                    <input name='verify' type='checkbox' value="<?= users::VERIFY?>"/>
                                </div>
                            </li>
                            <li>
                                <div>
                                    <p>Administrator</p>
                                </div>
                                <div><input name='admin' type='checkbox' value="<?= users::ADMIN?>"/></div>
                            </li>
                        </ul>
                    </div>
                    <div class="margin10Top aligncenter">
                        <span>Current Status</span>
                        <input type="checkbox" name="active" checked value="active" />Active
                    </div>
                </form>
                <?php
            }
        }

        public function isLabOpen() {
            $state = $this->model->getOne( [
                'table' => 'labOpen',
                'where' => 'id=?',
                'params' => [1]
            ] );
            return boolval( $state['open'] );
		}

		public function toggleLabOpen() {
			$isOpen = $this->isLabOpen();
			$state = $this->model->update( [
				'table' => 'labOpen',
				'update' => 'open=?',
				'where' => 'id=?',
				'params' => [(int)!$isOpen, 1]
			] );
            $this->app->loadPage( "home" );
		}
    }


    