<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/26/2018 13:29
	 */
	class Regex {
		public static $PASSWORD = "/.*(?=.{10,})(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[&\"'(\-_)=~#{[|`\\^@\]}^$*???%,;:!?.\/?+]).*/";
		public static $STRONG_PASSWORD = "/^(?!.*(.)\1{1})(?=(.*[\d]){2,})(?=(.*[a-z]){2,})(?=(.*[A-Z]){2,})(?=(.*[@#$%!]){2,})(?:[\da-zA-Z@#$%!]){15,100}$/";
		public static $EMAIL = "/[a-z0-9!#$%&\'*+\/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&\'*+\/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/";
		public static $NAME = "/^[A-Z a-záàÀâÂäÄãÃåÅæÆçÇéÉèÈêÊëËíÍìÌîÎïÏñÑóÓòÒôÔöÖõÕøØœŒßúÚùÙûÛüÜ]{2,50}$/";

		public static function test( $regex, $string ){
			if( preg_match( $regex, $string ) ){
				return true;
			}
			return false;
		}

		public static function range( $str, $min, $max = -1 ){
			$l = strlen( $str );
			if( $max != -1 ){
				return $l >= $min && $l < $max;
			} else {
				return $l >= $min;
			}
		}
	}
