<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 7/17/2018 16:45
	 * Created by IntelliJ IDEA.
	 */
	class Time {
        const YEAR = 31536000;  //60 * 60 * 24 * 365
        const MONTH = 2592000;  //60 * 60 * 24 * 30
        const WEEK = 604800;    //60 * 60 * 24 * 7
        const DAY = 86400;      //60 * 60 * 24
        const HOUR = 3600;      //60 * 60
        const MINUTE = 60;      //60
        const SECOND = 1;

        private static $timeChunks = [
            [ self::YEAR, 'year', 'y' ],
            [ self::MONTH, 'month', 'M' ],
            [ self::WEEK, 'week', 'w' ],
            [ self::DAY, 'day', 'd' ],
            [ self::HOUR, 'hour', 'h' ],
            [ self::MINUTE, 'minute', 'm' ],
            [ self::SECOND, 'second', 's' ]
        ];
        /**
		 * turns mysql datetime to a html5 input format
		 * @param $d
		 * @param bool|false $return
		 * @return bool|string
		 */
		public static function datetimeFormat( $d, $return = false ){
			if( $return ){
				return date( 'Y-m-d\TH:i', strtotime( $d ) );
			}
			echo date( 'Y-m-d\TH:i', strtotime( $d ) );
		}

		/**
		 * converts a database time to unix timestamp
		 * @param $str
		 * @return int
		 */
		public static function dbToUnix( $str ){
			return strtotime( $str );
		}

		/**
		 * Converts the machine time to human readable time
		 * @param $date
		 * @param string $format
		 * @return bool|string
		 */
		public static function humanDate( $date, $format = "n/j/y g:i A" ){
			date_default_timezone_set('America/Los_Angeles');
			return date( $format, strtotime( $date ) );
		}

		/**
		 * if the date now is before the date in question return true
		 * @param $unixDate int unix timestamp of date
		 * @return bool true if date is before the time now
		 */
		public static function dateBeforeNow( $unixDate ){
			if( time() < $unixDate ){
				return true;
			}
			return false;
		}

		/**
		 * if the date now is before the date in question return true
		 * @param $stringDate string unix timestamp of date
		 * @return bool true if date is before the time now
		 */
		public static function dateBeforeNowStr( $stringDate ){
			return self::dateBeforeNow( self::dbToUnix( $stringDate ) );
		}

		/**
		 * if the date now is after the date in question return true
		 * @param $unixDate int unix timestamp of date
		 * @return bool true if date is after the time now
		 */
		public static function dateAfterNow( $unixDate ){
			if( time() > $unixDate ){
				return true;
			}
			return false;
		}

		/**
		 * if the date now is after the date in question return true
		 * @param $stringDate int unix timestamp of date
		 * @return bool true if date is after the time now
		 */
		public static function dateAfterNowStr( $stringDate ){
			return self::dateAfterNow( self::dbToUnix( $stringDate ) );
		}

		/**
		 * @param int $datetime unix timestamp
		 * @param int $now current time now
		 * @param bool|false $print either the function should print or return an array in the following format
		 * [ amount => 30, measure => minute ]
		 * @return array
		 */
		public static function epochTime( $datetime, $now = -1, $print = false ){
			$now = ( ( $now == -1 ) ? ( time() ) : ( $now ) );
 			$datetime = $now - $datetime;

			$count = 0;
			$name = self::$timeChunks[0][1];

			for ( $i = 0, $j = count( self::$timeChunks ); $i < $j; $i++ ) {
				$seconds = self::$timeChunks[$i][0];
				$name = self::$timeChunks[$i][1];
				if ( ( $count = floor( $datetime / $seconds ) ) != 0 ) {
					break;
				}
			}

			$result = [
				'amount' => $count,
				'measure' => $name
			];

			if( $print ){
				echo ( ( $count != 1 ) ? ( "$count ${name}s ago" ) : ( "$count $name ago" ) );
			} else {
				return $result;
			}
		}

		public static function getTimeChunksFromSeconds( $secs, $str = false, $timeUnits = 'yMwdhms' ){
		    $n = time();
		    return self::getTimeChunks( $n - (int)$secs, $n, $str, $timeUnits );
        }

        public static function getTimeChunks( $datetime, $now = -1, $str = false, $timeUnits = 'yMwdhms' ) {
            $now = ( ( $now == -1 ) ? ( time() ) : ( $now ) );
            $datetime = $now - $datetime;

            $count = 0;
            $name = self::$timeChunks[0][1];

            $results = [];
            for ( $i = 0, $j = count( self::$timeChunks ); $i < $j; $i++ ) {
                if(!empty($timeUnits) && self::$timeChunks[$i][2] == $timeUnits[0] ) {
                    $seconds = self::$timeChunks[ $i ][ 0 ];
                    $name = self::$timeChunks[ $i ][ 1 ];
                    if ( ( $count = floor( $datetime / $seconds ) ) != 0 ) {
                        $results[] = [ $count, $name ];
                        $datetime = $datetime - $count * $seconds;
                    }
                    $timeUnits = substr( $timeUnits, 1 );
                }
            }

            if( $str ){
                $str = '';
                foreach ( $results as $item ) {
                    $str .= "${item[0]} ${item[1]}" . ( ( $item[0] != 1 ) ? ( 's ' ) : ( ' ' ) );
                }
                return trim( $str );
            } else {
                return $results;
            }
        }
	}