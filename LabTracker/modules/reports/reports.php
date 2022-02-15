<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 8/8/21 2:05 AM
     */

    class reports extends module {

        /**
         * @inheritDoc
         */
        public function fetch( $options = array() ) {
            // TODO: Implement fetch() method.
            $options = Core::getOptions( [
                'term'=>-1,
                'fields' => 'term,current',
                'where'=>'',
                'params' => [],
                'table' => 'terms'
            ], $options );
            $terms = $this->model->get( $options );
            return $terms;
        }

        /**
         * @inheritDoc
         */
        public function fetchOne( $options = array() ) {
            // TODO: Implement fetch() method.
            $options = Core::getOptions( [
                'term'=>-1,
                'fields' => '*',
                'where'=>'',
                'params' => [],
                'table' => 'terms'
            ], $options );
            if($options['term']!=-1){
                $options['where'] = 'term=?';
                array_push( $options['params'], $options['term'] );
            }
            $terms = $this->model->getOne( $options );
            return $terms;
            
        }

        public function fetchStudentCourses( $options = []){
            $options = Core::getOptions( [
                'term' => -1,
                'verified' => -1,
                'sid' => -1,
                'section'=>-1,
                'fields' => 'c.section,sc.sectionID,c.name,s.id,s.fname,s.lname',
                'where' => '',
                'params' => [],
                'table' => 'studentXcourses as sc inner join courses as c on sc.sectionID = c.id inner join students as s on sc.sid=s.id',
                'order' => 'c.section,c.name,s.id,s.fname,s.lname'
            ], $options );
            //to be added
            if($options['term']!=-1&&$options['verified'] != -1&& $options['sid'] !=-1){
                $options['where'] = 'c.term=? && sc.verified=? && sc.sid=?';
                array_push( $options['params'], $options['term'] );
                array_push( $options['params'], $options['verified'] );
                array_push( $options['params'], $options['sid'] );
            }
            else if($options['term']!=-1&&$options['verified'] != -1&& $options['section'] !=-1){
                $options['where'] = 'c.term=? && sc.verified=? && c.section=?';
                array_push( $options['params'], $options['term'] );
                array_push( $options['params'], $options['verified'] );
                array_push( $options['params'], $options['section'] );
            }
            else if($options['term']!=-1&&$options['verified']){
                $options['where'] = 'c.term=? && sc.verified=?';
                array_push( $options['params'], $options['term'] );
                array_push( $options['params'], $options['verified'] );
            }
            
            $courses = $this->model->get( $options );
            return $courses;
        }

		/**
		 * report by term
		 * @param $term
		 * @param bool $csv
		 * @return array|false|string
		 */
		private function reportByTerm( $term, $csv = false) {
			$reports = $this->fetchStudentCourses( [ 'term' => $term[ 'term' ], 'verified' => 1 ] );
			if ( $reports === false ) {
				return Ajax::response( [], false, "There was an issue getting the reports." );
			} else {
				foreach ( $reports as $key => $item ) {
					$startdate = strtotime( $term[ 'startDate' ] );
					$enddate = strtotime( $term[ 'endDate' ] );
					$reports[ $key ][ 'hours' ] = $this->getTotalTime( $item[ 'id' ], $item[ 'sectionID' ], $startdate, $enddate, 'hm' );
					$reports[ $key ][ 'clkhours' ] =  $this->getTotalTime( $item[ 'id' ], $item[ 'sectionID' ], $startdate, $enddate, 'hm', true );
					$weeks = 0;
					$startdate = $term[ 'startDate' ];
					$startweek = strtotime( $startdate . '+' . $weeks . ' week' );
					$endweek = strtotime( $startdate . '+' . ( $weeks + 1 ) . ' week' );

					while ( $startweek < $enddate ) {
						if ( $enddate < $endweek ) {
							//last week
							$reports[ $key ][ 'week' . $weeks ] = $this->getTotalTime( $item[ 'id' ], $item[ 'sectionID' ], $startweek, $enddate, 'hm' );
						} else {
							//any other week
							$reports[ $key ][ 'week' . $weeks ] = $this->getTotalTime( $item[ 'id' ], $item[ 'sectionID' ], $startweek, $endweek, 'hm' );
						}

						$weeks = $weeks + 1;
						$startweek = strtotime( $startdate . '+' . $weeks . ' week' );
						$endweek = strtotime( $startdate . '+' . ( $weeks + 1 ) . ' week' );
					}
				}

                if( $csv ){
					return [ 'reports' => $reports, 'weeks' => $weeks ];
                } else {
					return Ajax::response( [ 'reports' => $reports, 'weeks' => $weeks ], true, "" );
				}
			}
		}

		/**
         * report gen by student(total)
		 * @param array $inData
         * @param boolean $csv
		 * @return false|array|string
		 */
		private function reportByStudent( $inData = [], $csv = false ){
			$term = $this->fetchOne( [ 'term' => $inData[ 'term' ] ] );
			$this->app->loadModule("courses");

			$startdate = strtotime( $term[ 'startDate' ] );
			$enddate = strtotime( $term[ 'endDate' ] );
			$reports = $this->fetchStudentCourses( [ 'term' => $inData[ 'term' ], 'verified' => 1, 'sid' => $inData[ 'studentid' ] ] );
			if ( $reports === false ) {
				return Ajax::response( [], false, "There are no students records from that student and that term." );
			} else {
				foreach ( $reports as $key => $item ) {
					$course = $this->app->courses->fetchOne( ['section' => $item['section'] ] );
					$reports[ $key ][ 'hours' ] = $this->getTotalTime( $item[ 'id' ], $course[ 'id' ], $startdate, $enddate, 'hm' );
				}
                if( $csv )
                    return [ 'reports' => $reports ];
				return Ajax::response( [ 'reports' => $reports ], true );
			}
        }

		/**
         * report gen by student(details
		 * @param array $inData
         * @param boolean $csv
		 * @return false|string|array
		 */
        private function reportByStudentDetails( $inData = [], $csv = false ){
			//select s.fname, s.lname, t.timein, t.timeout, t.section, t.term from timeLogs as t inner join students as s on t.sid = s.id where t.sid='2358174' order by t.section;
			$data = $this->model->get([
				'fields' => 't.sid,s.fname, s.lname, t.timein, t.timeout, t.timeout-t.timein as sum, c.name as class, c.professor, c.section, t.term',
				'table' => 'timeLogs as t inner join students as s on t.sid = s.id inner join courses as c on t.section = c.id',
				'where' => 't.sid=? && t.term=? && t.timeout!=-1',
				'params' => [ $inData['studentid'], $inData['term'] ],
				'order' => 't.timein'
			]);

			//remap the data
			$remap = [];
			foreach ( $data as $item ) {
				$section = $item['section'];
				if( !isset( $remap[ $section ] ) ){
					$remap[ $section ] = [];
				}
				$remap[$section][] = $item;
			}

            if( $csv )
                return $remap;


			unset( $data );
			ksort( $remap );
			$data = <<<EOQ
            <table id="ReportsTable" class="dataTable">
                <thead>
                <tr>
                    <td>Student Id</td>
                    <td>Student Name</td>
                    <td>Class</td>
                    <td>Section #</td>
                    <td>Time In</td>
                    <td>Time Out</td>
                    <td>Session</td>
                    <td>Running Total</td>
                </tr>
                </thead>
                <tbody>
EOQ;
            foreach ($remap as $k => $v){
                $name = $v[0]['class'];
                $running = 0;
				$data .= "<tr><td colspan='8'>Section number: $k - $name</td></tr>";
                foreach ( $v as $item ) {

					$data .= "<tr>";
					$data .= "<td>${item['sid']}</td>";
					$data .= "<td>" . ucwords( strtolower( $item['lname'] .', '. $item['fname']) ) . "</td>";
					$data .= "<td>${item['class']}</td>";
					$data .= "<td>${item['section']}</td>";
					$s = date( "n/j/y g:i A", (int)$item['timein'] );
					$data .= "<td>" . $s. "</td>";
					$s = date( "n/j/y g:i A", (int)$item['timeout'] );
					$data .= "<td>" . $s . "</td>";
					$data .= "<td>" . Time::getTimeChunksFromSeconds( $item['sum'], true, 'hm' ) . "</td>";
                    $running += $item['sum'];
					$data .= "<td>" . Time::getTimeChunksFromSeconds( $running, true, 'hm' ) . "</td>";
					$data .= "</tr>";

                }
				$data .= "<tr><td colspan='8' class='alignrightImp'>Total time: " . Time::getTimeChunksFromSeconds( $running, true, 'hms' ) . "</td></tr>";
            }
            $data .= "</tbody></table>";
            return Ajax::response( ['data'=>$data], true, '', 'raw');
        }

		/**
         * report gen by a date range
		 * @param array $inData
         * @param boolean $csv
		 * @return false|string|array
		 */
		private function reportByDateRange( $inData = [], $csv = false ){
			$startdate = strtotime( $inData[ 'startdate' ] );
			$enddate = strtotime( $inData[ 'enddate' ] );
			if ( $startdate === false || $enddate === false || $startdate > $enddate ) {
				return Ajax::response( [], false, "The start date needs to be before the end date." );
			} else {
				$reports = $this->fetchStudentCourses( [ 'term' => $inData[ 'term' ], 'verified' => 1 ] );
				if ( $reports === false ) {
					return  Ajax::response( [], false, "There are no students records from those dates." );
				} else {
					foreach ( $reports as $key => $item ) {
						$reports[ $key ][ 'hours' ] = $this->getTotalTime( $item[ 'id' ], $item[ 'sectionID' ], $startdate, $enddate, 'hm' );
					}
                    if( $csv )
                        return [ 'reports' => $reports ];
					return  Ajax::response( [ 'reports' => $reports ], true );
				}
			}
		}

		/**
         * report gen by section number
		 * @param array $inData
         * @param boolean $csv
		 * @return false|array|string
		 */
		private function reportByClassSection( $inData = [], $csv = false ){
			$term = $this->fetchOne( [ 'term' => $inData[ 'term' ] ] );
			$this->app->loadModule("courses");
			$course = $this->app->courses->fetchOne( ['section' => $inData['section'] ] );
			if( $course !== false ) {
				$startdate = strtotime( $term[ 'startDate' ] );
				$enddate = strtotime( $term[ 'endDate' ] );
			    if( !empty( $inData['startdate'] ) )
					$startdate = strtotime( $inData['startdate'] );
				if( !empty( $inData['enddate'] ) )
					$enddate = strtotime( $inData['enddate'] );

				$reports = $this->fetchStudentCourses( [ 'term' => $inData[ 'term' ], 'verified' => 1, 'section' => $inData[ 'section' ] ] );
				if ( $reports === false ) {
					return Ajax::response( [], false, "There are no students records from that student and that term." );
				} else {
					foreach ( $reports as $key => $item ) {
						$reports[ $key ][ 'hours' ] = $this->getTotalTime( $item[ 'id' ], $course[ 'id' ], $startdate, $enddate, 'hms' );
					}
                    if( $csv )
                        return [ 'reports' => $reports ];
					return Ajax::response( [ 'reports' => $reports ], true );
				}
			} else {
				return Ajax::response( [], false, "Not a valid section" );
            }
        }

		/**
		 * main action of the report creation page. calls subsequent report functions
		 * @param $csv
		 */
        public function report() {
            $_POST = Security::sanitize( $_POST ); //David: gotta clean up input data from users prevents mysql injects. Never trust your user
            if ( isset( $_POST[ 'TermReport' ] ) ) {
                $term = $this->fetchOne( [ 'term' => $_POST[ 'TermReport' ] ] );
                $data = "";
                if ( $term === false ) {
                    $data = Ajax::response( [], false, "That term does not exist." );
                } else {
                    //report by term
                    $data = $this->reportByTerm( $term );                }
                echo $data;
            } else if ( isset( $_POST[ 'startdate' ] ) && isset( $_POST[ 'enddate' ] ) && !isset( $_POST['section'] ) ) {
                $data = $this->reportByDateRange( $_POST );
                echo $data;
            } else if ( isset( $_POST[ 'studentid' ] ) && isset( $_POST[ 'term' ] )  && ( isset( $_POST['details'] ) && $_POST['details'] == 0 ) )  {
                $data = $this->reportByStudent( $_POST );
                echo $data;
            } else if ( isset( $_POST[ 'studentid' ] ) && isset( $_POST[ 'term' ] )  && ( isset( $_POST['details'] ) && $_POST['details'] == 1 ) )  {
				$data = $this->reportByStudentDetails( $_POST );
				echo $data;
			} else if ( isset( $_POST[ 'section' ] ) && isset( $_POST[ 'term' ] ) ) {
                //report by class section
                $data = $this->reportByClassSection( $_POST );
                echo $data;
            } else if ( isset( $_POST[ 'terms' ] ) ) {
                $terms = $this->fetch( [] );
                echo Ajax::response( [ 'terms' => $terms ], true );

            } else {
                $this->loadView( "report" );
            }

        }

		/**
         * download report as a csv
		 * @param $report
		 */
        public function download( $report ){
            $report = Security::sanitize( $report );
            $_POST = Security::sanitize( $_POST );
			$this->app->loadModule( 'files' );

//            Debug::println($_POST);
            switch ( $report ){
                case 'term' :
					$term = $this->fetchOne( [ 'term' => $_POST[ 'TermReport' ] ] );

					if ( $term === false ) {
						//TODO display error
					}
                    $data = $this->reportByTerm( $term, true );
                    $csv = [
                        'headers' => ['FirstName', 'LastName', 'StudentId', 'Class', 'Section#', 'CumulativeHours', 'CumulativeHours(hh:mm)'],
                        'data' => []
                    ];
                    for( $i = 0; $i < $data['weeks']; $i++ ){
                        $csv['headers'][] = 'Week' . ($i+1);
                    }

					foreach ( $data[ 'reports' ] as $item ) {
                        $a = [
							$item['fname'],
							$item['lname'],
							$item['id'],
							$item['name'],
							$item['section'],
							$item['hours'],
							$item['clkhours']
						];
						for( $i = 0; $i < $data['weeks']; $i++ ){
							$a[] = $item['week' . ($i)];
						}
						$csv['data'][] = $a;
					}
//                    Debug::println( $csv );
					$this->app->files->getDataAsCsv( $csv );
                    break;
                case 'section':
					$data = $this->reportByClassSection( $_POST, true );
                    $csv = [
                        'headers' => ['FirstName', 'LastName', 'StudentId', 'Class', 'Section#', 'CumulativeHours'],
                        'data' => []
                    ];
					foreach ( $data[ 'reports' ] as $item ) {
                        $csv['data'][] = [
                            $item['fname'],
                            $item['lname'],
                            $item['id'],
                            $item['name'],
                            $item['section'],
                            $item['hours']
                        ];
                    }
					$this->app->files->getDataAsCsv( $csv );
//					Debug::println( $csv );
                    break;
                case 'student':
					$data = $this->reportByStudent( $_POST, true );
					$csv = [
						'headers' => ['FirstName', 'LastName', 'StudentId', 'Class', 'Section#', 'CumulativeHours'],
						'data' => []
					];
					foreach ( $data[ 'reports' ] as $item ) {
						$csv['data'][] = [
							$item['fname'],
							$item['lname'],
							$item['id'],
							$item['name'],
							$item['section'],
							$item['hours']
						];
					}
					$this->app->files->getDataAsCsv( $csv );
                    break;
                case 'studentDetails':
					$data = $this->reportByStudentDetails( $_POST, true);
					$csv = [
						'headers' => ['StudentId', 'StudentName', 'Class', 'Section#', 'TimeIn', 'TimeOut', 'Session', 'RunningTotal'],
						'data' => []
					];
					foreach ( $data as $k => $v ) {
						$name = $v[0]['class'];
                        $csv['data'][] = ["Section number: $k - $name"];
                        $running = 0;
						foreach ( $v as $item ) {
							$csv['data'][] = [
								$item['sid'],
								$item['lname'] .', '. $item['fname'],
								$item['class'],
								$item['section'],
								date( "n/j/y g:i A", (int)$item['timein'] ),
								date( "n/j/y g:i A", (int)$item['timeout'] ),
								Time::getTimeChunksFromSeconds( $item['sum'], true, 'hm' ),
								Time::getTimeChunksFromSeconds( $running, true, 'hm' )
							];
							$running += $item['sum'];
						}
						$csv['data'][] = [ "Total time: " . Time::getTimeChunksFromSeconds( $running, true, 'hm' )];

                    }
					$this->app->files->getDataAsCsv( $csv );
                    //Debug::println( $data );
                    break;
                case 'date':
					$data = $this->reportByDateRange( $_POST, true );
					$csv = [
						'headers' => ['FirstName', 'LastName', 'StudentId', 'Class', 'Section#', 'CumulativeHours'],
						'data' => []
					];
					foreach ( $data[ 'reports' ] as $item ) {
						$csv['data'][] = [
							$item['fname'],
							$item['lname'],
							$item['id'],
							$item['name'],
							$item['section'],
							$item['hours']
						];
					}
					$this->app->files->getDataAsCsv( $csv );
                    break;
            }
        }

		/**
		 * @param string $sid student id
		 * @param string $section
		 * @param string $start
		 * @param string $end
		 * @param string $timeUnits
		 * @return array|string
		 */
        public function getTotalTime( $sid, $section,$start,$end, $timeUnits = 'hms', $clkFormat = false ){
            //SELECT id, sid, SUM(timeout - timein) FROM labtracker.timeLogs where sid = ? AND timein>=? AND timeout <=? AND section=? AND timeout IS NOT NULL && timeout !=-1;
            $options = [
                'table' => 'timeLogs',
                'fields' => 'id, sid, (timeout - timein) as sum',
                'where' => 'sid=? && timein >=? && timeout <= ? && section=? && timeout IS NOT NULL && timeout !=-1',
                'params' => [ $sid,$start,$end,$section ]
            ];
            $d = $this->model->get( $options );
            if( isset( $d ) && count($d)>0 ){
                $sum = 0;
                foreach ( $d as $item ) {
                    $sum += $item['sum'];
                }
                if( $clkFormat ){
                    $h = floor( $sum / Time::HOUR );
                    $m = floor( ( $sum - ( $h * Time::HOUR ) ) / Time::MINUTE );
                    $h .= '';
                    $m .= '';
                    $h = str_pad( $h, 2, '0', STR_PAD_LEFT );
                    $m = str_pad( $m, 2, '0', STR_PAD_LEFT );
                    return $h .':' .$m;
                } else {
					$time = Time::getTimeChunksFromSeconds( $sum, true, $timeUnits );
					return $time ? $time : "0 hours";
				}
            }
            else {
                return $clkFormat ? '00:00' : '0 hours';
            }
        }

        public function studentReport( $params ){
            $params = Security::sanitize( $params );
            //select s.fname, s.lname, t.timein, t.timeout, t.section, t.term from timeLogs as t inner join students as s on t.sid = s.id where t.sid='2358174' order by t.section;
            $data = $this->model->get([
                'fields' => 't.sid,s.fname, s.lname, t.timein, t.timeout, t.timeout-t.timein as sum, c.name as class, c.professor, t.section, t.term',
                'table' => 'timeLogs as t inner join students as s on t.sid = s.id inner join courses as c on t.section = c.section',
                'where' => 't.sid=? && t.term=?',
                'params' => [ $params[0], $params[1] ],
                'order' => 't.section'
            ]);

            //remap the data
            $remap = [];
            foreach ( $data as $item ) {
                $section = $item['section'];
                if( !isset( $remap[ $section ] ) ){
                    $remap[ $section ] = [];
                }
                $remap[$section][] = $item;
            }


            unset( $data );
            //Ajax::successResponse( $remap );
            ?>
            <table class="dataTable">
                <thead>
                <tr>
                    <td>Student Id</td>
                    <td>Student Name</td>
                    <td>Class</td>
                    <td>Section #</td>
                    <td>Time In</td>
                    <td>Time Out</td>
                    <td>Session</td>
                    <td>Running Total</td>
                </tr>
                </thead>
                <tbody>
                <?php
                    foreach ($remap as $k => $v){
                        $name = $v[0]['class'];
                        $running = 0;
                        echo "<tr><td colspan='8'>Section number: $k - $name</td></tr>";
                        foreach ( $v as $item ) {

                            echo "<tr>";
                            echo "<td>${item['sid']}</td>";
                            echo "<td>" . ucwords( strtolower( $item['lname'] .', '. $item['fname']) ) . "</td>";
                            echo "<td>${item['class']}</td>";
                            echo "<td>${item['section']}</td>";
                            echo "<td>" . Time::humanDate( $item['timein'] ) . "</td>";
                            echo "<td>" . Time::humanDate( $item['timeout'] ) . "</td>";
                            echo "<td>" . Time::getTimeChunksFromSeconds( $item['sum'], true, 'hms' ) . "</td>";
                            $running += $item['sum'];
                            echo "<td>" . Time::getTimeChunksFromSeconds( $running, true, 'hms' ) . "</td>";
                            echo "</tr>";

                        }
                        echo "<tr><td colspan='8' class='alignrightImp'>Total time: " . Time::getTimeChunksFromSeconds( $running, true, 'hms' ) . "</td></tr>";
                    }
                ?>
                </tbody>
            </table>
            <?php

        }
    }