<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 3/20/2018 13:34
	 */
	class UI {
		const CHECKED = 1;
		const UNCHECKED = 0;
		const INDETERMINATE = 2;

		static function checkbox( $text, $name, $checked = self::UNCHECKED, $intedeterminate = false, $class = '', $attrs = array() ){
			if ( isset( $attrs['class'] ) ) {
				$class = $attrs['class'];
				unset( $attrs['class'] );
			}
			$attrStr ='';
			foreach ( $attrs as $attr => $val ) {
				$attrStr .= $attr . '="' . $val . '" ';
			}

			?>
			<div class='ui-checkbox <?=$class?>' <?= $attrStr ?> name="<?= $name?>" data-checked="<?=$checked?>" <?= $intedeterminate? 'data-indeterminate="1"':''?>>
				<input type="hidden" class="none" name="<?= $name ?>" value="<?=$checked?>">
				<div class="clickable">
					<?php if( $checked == self::CHECKED ) {?>
						<i class="fas fa-check" aria-hidden="true"></i>
					<?php } else if( $checked == self::INDETERMINATE ) {?>
						<i class="fas fa-square" aria-hidden="true"></i>
					<?php } else { ?>
						<i>&nbsp;</i>
					<?php } ?>
				</div>
				<span class="text"><?= $text ?></span>
			</div>
			<?php
		}

		static function radio( $text, $name, $checked = self::UNCHECKED, $class = '', $attrs = [] ){//$name, $checked = self::UNCHECKED, $class = '', $attrs = array() ){
			if ( isset( $attrs['class'] ) ) {
				$class = $attrs['class'];
				unset( $attrs['class'] );
			}
			$attrStr ='';
			foreach ( $attrs as $attr => $val ) {
				$attrStr .= $attr . '="' . $val . '" ';
			}
			?>
			<div class='ui-radio <?=$class?>' <?= $attrStr ?> name="<?= $name?>" data-checked="<?=$checked?>">
				<input type="hidden" class="none" <?= ( $checked ? ( "name='$name'" ) : '' ) ?> value="<?=$checked?>">
				<div class="clickable"><?php if( $checked == self::CHECKED ) {?>
						<i class="fas fa-circle" aria-hidden="true"></i>
					<?php } else { ?><i>&nbsp;</i><?php } ?>
				</div>
				<span class="text"><?= $text ?></span>
			</div>
			<?php
		}

		static function codeLanguagesSelect( $name, $multi = false, $data = array() ){
			?>
			<select name="<?= $name ?>" <?= $multi ? 'multiple="multiple"' : '' ?>>
				<?php
					$arr = [];
					foreach ( $data as $item ) {
						$arr[] = $item['name'];
					}
				?>
				<option value="c_cpp" data-id="1" <?=Core::inArray('c', $arr )?'selected':''?>>C</option>
				<option value="c_cpp" data-id="2" <?=Core::inArray('c++', $arr)?'selected':''?>>C++</option>
				<option value="java" data-id="3" <?=Core::inArray('java', $arr)?'selected':''?>>Java</option>
				<option value="python" data-id="5" <?=Core::inArray('python', $arr)?'selected':''?>>Python</option>
			</select>
			<?php
		}

		static function fileInput( $name, $button = 'upload', $class = '', $accept = '*/*' ){
			?>
			<div class="ui-fileinput <?=$class?>" name="<?=$name?>">
				<button type="file" class="upload" >
					<i class="fas fa-upload" aria-hidden="true"></i>&nbsp;<?=$button?>
				</button>
				<div class="relative inline">
					<input type="text" class="ui-fileinput-text" />
					<span class="delete"><i class="fas fa-times" aria-hidden="true"></i></span>
				</div>
				<input type="file" name="<?=$name?>" style="display: none;" accept="<?=$accept?>" />
			</div>
			<?php
		}

		static function meteredTextarea( $name, $val = '', $limit = -1, $classes = '' ){
			?>
			<div class="ui-meteredTextarea <?= $classes ?>">
				<textarea tab class="<?=$classes?>" meter='<?=$limit?>' name="<?=$name?>"><?= Core::mewLineToEntity( $val )?></textarea>
				<span class="bytes"><?=mb_strlen( $val )?> Bytes</span>
			</div>
			<?php
		}

		static function calendarTimeIcon( $input, $cal = true, $time = true){
			?>
			<div class="caltime">
				<?= $input ?>
				<div>
					<?php if( $cal ) { ?>
					<i class="fas fa-calendar-alt" aria-hidden="true"></i>
					<?php } if( $time ) { ?>
					<i class="fas fa-clock" aria-hidden="true"></i>
					<?php } ?>
				</div>
			</div>
			<?php
		}

		static function copyInput( $val, $class = '' ){
			?>
			<div class="ui-copyinput <?= $class ?>">
				<input readonly type="text" value="<?= $val ?>" />
				<button class="tooltip" title="Copy">
					<i class="far fa-clipboard" aria-hidden="true" ></i>
				</button>

			</div>
			<?php
			return '';
		}

		static function returnCopyInput( $val, $class = '' ){
			$str = '<div class="ui-copyinput ' . $class .'">'.
				'<input readonly type="text" value="' . $val . '" />'.
				'<button class="tooltip" title="Copy">'.
					'<i class="far fa-clipboard" aria-hidden="true" ></i>'.
				'</button>'.
			'</div>';
			return $str;
		}

		static function ajaxLoaderBars(){
			?>
			<div class="ui-ajaxloader">
				<div class="rect1"></div>
				<div class="rect2"></div>
				<div class="rect3"></div>
				<div class="rect4"></div>
				<div class="rect5"></div>
			</div>
			<?php
		}

		public static function utcSelect( $selected = 0, $name = 'timezone' ){
			?>
			<select class="autoload" name="<?= $name ?>">
				<option timeZoneId="1"  gmtAdjustment="GMT-12:00" useDaylightTime="0" <?= $selected == -12 ? 'selected ' : '' ?>value="-12">(GMT-12:00) International Date Line West</option>
				<option timeZoneId="2"  gmtAdjustment="GMT-11:00" useDaylightTime="0" <?= $selected == -11 ? 'selected ' : '' ?>value="-11">(GMT-11:00) Midway Island, Samoa</option>
				<option timeZoneId="3"  gmtAdjustment="GMT-10:00" useDaylightTime="0" <?= $selected == -10 ? 'selected ' : '' ?>value="-10">(GMT-10:00) Hawaii</option>
				<option timeZoneId="4"  gmtAdjustment="GMT-09:00" useDaylightTime="1" <?= $selected == -9 ? 'selected ' : '' ?>value="-9">(GMT-09:00) Alaska</option>
				<option timeZoneId="6"  gmtAdjustment="GMT-08:00" useDaylightTime="1" <?= $selected == -8 ? 'selected ' : '' ?>value="-8">(GMT-08:00) Tijuana, Baja California</option>
				<option timeZoneId="5"  gmtAdjustment="GMT-08:00" useDaylightTime="1" <?= $selected == -8 ? 'selected ' : '' ?>value="-8">(GMT-08:00) Pacific Time (US & Canada)</option>
				<option timeZoneId="7"  gmtAdjustment="GMT-07:00" useDaylightTime="0" <?= $selected == -7 ? 'selected ' : '' ?>value="-7">(GMT-07:00) Arizona</option>
				<option timeZoneId="9"  gmtAdjustment="GMT-07:00" useDaylightTime="1" <?= $selected == -7 ? 'selected ' : '' ?>value="-7">(GMT-07:00) Mountain Time (US & Canada)</option>
				<option timeZoneId="8"  gmtAdjustment="GMT-07:00" useDaylightTime="1" <?= $selected == -7 ? 'selected ' : '' ?>value="-7">(GMT-07:00) Chihuahua, La Paz, Mazatlan</option>
				<option timeZoneId="11" gmtAdjustment="GMT-06:00" useDaylightTime="1" <?= $selected == -6 ? 'selected ' : '' ?>value="-6">(GMT-06:00) Central Time (US & Canada)</option>
				<option timeZoneId="10" gmtAdjustment="GMT-06:00" useDaylightTime="0" <?= $selected == -6 ? 'selected ' : '' ?>value="-6">(GMT-06:00) Central America</option>
				<option timeZoneId="12" gmtAdjustment="GMT-06:00" useDaylightTime="1" <?= $selected == -6 ? 'selected ' : '' ?>value="-6">(GMT-06:00) Guadalajara, Mexico City, Monterrey</option>
				<option timeZoneId="13" gmtAdjustment="GMT-06:00" useDaylightTime="0" <?= $selected == -6 ? 'selected ' : '' ?>value="-6">(GMT-06:00) Saskatchewan</option>
				<option timeZoneId="14" gmtAdjustment="GMT-05:00" useDaylightTime="0" <?= $selected == -5 ? 'selected ' : '' ?>value="-5">(GMT-05:00) Bogota, Lima, Quito, Rio Branco</option>
				<option timeZoneId="16" gmtAdjustment="GMT-05:00" useDaylightTime="1" <?= $selected == -5 ? 'selected ' : '' ?>value="-5">(GMT-05:00) Indiana (East)</option>
				<option timeZoneId="15" gmtAdjustment="GMT-05:00" useDaylightTime="1" <?= $selected == -5 ? 'selected ' : '' ?>value="-5">(GMT-05:00) Eastern Time (US & Canada)</option>
				<option timeZoneId="17" gmtAdjustment="GMT-04:00" useDaylightTime="1" <?= $selected == -4 ? 'selected ' : '' ?>value="-4">(GMT-04:00) Atlantic Time (Canada)</option>
				<option timeZoneId="18" gmtAdjustment="GMT-04:00" useDaylightTime="0" <?= $selected == -4 ? 'selected ' : '' ?>value="-4">(GMT-04:00) Caracas, La Paz</option>
				<option timeZoneId="19" gmtAdjustment="GMT-04:00" useDaylightTime="0" <?= $selected == -4 ? 'selected ' : '' ?>value="-4">(GMT-04:00) Manaus</option>
				<option timeZoneId="20" gmtAdjustment="GMT-04:00" useDaylightTime="1" <?= $selected == -4 ? 'selected ' : '' ?>value="-4">(GMT-04:00) Santiago</option>
				<option timeZoneId="21" gmtAdjustment="GMT-03:30" useDaylightTime="1" <?= $selected == -3.5 ? 'selected ' : '' ?>value="-3.5">(GMT-03:30) Newfoundland</option>
				<option timeZoneId="22" gmtAdjustment="GMT-03:00" useDaylightTime="1" <?= $selected == -3 ? 'selected ' : '' ?>value="-3">(GMT-03:00) Brasilia</option>
				<option timeZoneId="23" gmtAdjustment="GMT-03:00" useDaylightTime="0" <?= $selected == -3 ? 'selected ' : '' ?>value="-3">(GMT-03:00) Buenos Aires, Georgetown</option>
				<option timeZoneId="24" gmtAdjustment="GMT-03:00" useDaylightTime="1" <?= $selected == -3 ? 'selected ' : '' ?>value="-3">(GMT-03:00) Greenland</option>
				<option timeZoneId="25" gmtAdjustment="GMT-03:00" useDaylightTime="1" <?= $selected == -3 ? 'selected ' : '' ?>value="-3">(GMT-03:00) Montevideo</option>
				<option timeZoneId="26" gmtAdjustment="GMT-02:00" useDaylightTime="1" <?= $selected == -2 ? 'selected ' : '' ?>value="-2">(GMT-02:00) Mid-Atlantic</option>
				<option timeZoneId="27" gmtAdjustment="GMT-01:00" useDaylightTime="0" <?= $selected == -1 ? 'selected ' : '' ?>value="-1">(GMT-01:00) Cape Verde Is.</option>
				<option timeZoneId="28" gmtAdjustment="GMT-01:00" useDaylightTime="1" <?= $selected == -1 ? 'selected ' : '' ?>value="-1">(GMT-01:00) Azores</option>
				<option timeZoneId="29" gmtAdjustment="GMT+00:00" useDaylightTime="0" <?= $selected == 0 ? 'selected ' : '' ?>value="0">(GMT+00:00) Casablanca, Monrovia, Reykjavik</option>
				<option timeZoneId="30" gmtAdjustment="GMT+00:00" useDaylightTime="1" <?= $selected == 0 ? 'selected ' : '' ?>value="0">(GMT+00:00) Greenwich Mean Time : Dublin, Edinburgh, Lisbon, London</option>
				<option timeZoneId="31" gmtAdjustment="GMT+01:00" useDaylightTime="1" <?= $selected == 1 ? 'selected ' : '' ?>value="1">(GMT+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna</option>
				<option timeZoneId="32" gmtAdjustment="GMT+01:00" useDaylightTime="1" <?= $selected == 1 ? 'selected ' : '' ?>value="1">(GMT+01:00) Belgrade, Bratislava, Budapest, Ljubljana, Prague</option>
				<option timeZoneId="33" gmtAdjustment="GMT+01:00" useDaylightTime="1" <?= $selected == 1 ? 'selected ' : '' ?>value="1">(GMT+01:00) Brussels, Copenhagen, Madrid, Paris</option>
				<option timeZoneId="34" gmtAdjustment="GMT+01:00" useDaylightTime="1" <?= $selected == 1 ? 'selected ' : '' ?>value="1">(GMT+01:00) Sarajevo, Skopje, Warsaw, Zagreb</option>
				<option timeZoneId="35" gmtAdjustment="GMT+01:00" useDaylightTime="1" <?= $selected == 1 ? 'selected ' : '' ?>value="1">(GMT+01:00) West Central Africa</option>
				<option timeZoneId="36" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Amman</option>
				<option timeZoneId="37" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Athens, Bucharest, Istanbul</option>
				<option timeZoneId="38" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Beirut</option>
				<option timeZoneId="39" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Cairo</option>
				<option timeZoneId="40" gmtAdjustment="GMT+02:00" useDaylightTime="0" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Harare, Pretoria</option>
				<option timeZoneId="41" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius</option>
				<option timeZoneId="42" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Jerusalem</option>
				<option timeZoneId="43" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Minsk</option>
				<option timeZoneId="44" gmtAdjustment="GMT+02:00" useDaylightTime="1" <?= $selected == 2 ? 'selected ' : '' ?>value="2">(GMT+02:00) Windhoek</option>
				<option timeZoneId="45" gmtAdjustment="GMT+03:00" useDaylightTime="0" <?= $selected == 3 ? 'selected ' : '' ?>value="3">(GMT+03:00) Kuwait, Riyadh, Baghdad</option>
				<option timeZoneId="46" gmtAdjustment="GMT+03:00" useDaylightTime="1" <?= $selected == 3 ? 'selected ' : '' ?>value="3">(GMT+03:00) Moscow, St. Petersburg, Volgograd</option>
				<option timeZoneId="47" gmtAdjustment="GMT+03:00" useDaylightTime="0" <?= $selected == 3 ? 'selected ' : '' ?>value="3">(GMT+03:00) Nairobi</option>
				<option timeZoneId="48" gmtAdjustment="GMT+03:00" useDaylightTime="0" <?= $selected == 3 ? 'selected ' : '' ?>value="3">(GMT+03:00) Tbilisi</option>
				<option timeZoneId="49" gmtAdjustment="GMT+03:30" useDaylightTime="1" <?= $selected == 3.5 ? 'selected ' : '' ?>value="3.5">(GMT+03:30) Tehran</option>
				<option timeZoneId="50" gmtAdjustment="GMT+04:00" useDaylightTime="0" <?= $selected == 4 ? 'selected ' : '' ?>value="4">(GMT+04:00) Abu Dhabi, Muscat</option>
				<option timeZoneId="51" gmtAdjustment="GMT+04:00" useDaylightTime="1" <?= $selected == 4 ? 'selected ' : '' ?>value="4">(GMT+04:00) Baku</option>
				<option timeZoneId="52" gmtAdjustment="GMT+04:00" useDaylightTime="1" <?= $selected == 4 ? 'selected ' : '' ?>value="4">(GMT+04:00) Yerevan</option>
				<option timeZoneId="53" gmtAdjustment="GMT+04:30" useDaylightTime="0" <?= $selected == 4.5 ? 'selected ' : '' ?>value="4.5">(GMT+04:30) Kabul</option>
				<option timeZoneId="54" gmtAdjustment="GMT+05:00" useDaylightTime="1" <?= $selected == 5 ? 'selected ' : '' ?>value="5">(GMT+05:00) Yekaterinburg</option>
				<option timeZoneId="55" gmtAdjustment="GMT+05:00" useDaylightTime="0" <?= $selected == 5 ? 'selected ' : '' ?>value="5">(GMT+05:00) Islamabad, Karachi, Tashkent</option>
				<option timeZoneId="56" gmtAdjustment="GMT+05:30" useDaylightTime="0" <?= $selected == 5.5 ? 'selected ' : '' ?>value="5.5">(GMT+05:30) Sri Jayawardenapura</option>
				<option timeZoneId="57" gmtAdjustment="GMT+05:30" useDaylightTime="0" <?= $selected == 5.5 ? 'selected ' : '' ?>value="5.5">(GMT+05:30) Chennai, Kolkata, Mumbai, New Delhi</option>
				<option timeZoneId="58" gmtAdjustment="GMT+05:45" useDaylightTime="0" <?= $selected == 5.75 ? 'selected ' : '' ?>value="5.75">(GMT+05:45) Kathmandu</option>
				<option timeZoneId="59" gmtAdjustment="GMT+06:00" useDaylightTime="1" <?= $selected == 6 ? 'selected ' : '' ?>value="6">(GMT+06:00) Almaty, Novosibirsk</option>
				<option timeZoneId="60" gmtAdjustment="GMT+06:00" useDaylightTime="0" <?= $selected == 6 ? 'selected ' : '' ?>value="6">(GMT+06:00) Astana, Dhaka</option>
				<option timeZoneId="61" gmtAdjustment="GMT+06:30" useDaylightTime="0" <?= $selected == 6.5 ? 'selected ' : '' ?>value="6.5">(GMT+06:30) Yangon (Rangoon)</option>
				<option timeZoneId="62" gmtAdjustment="GMT+07:00" useDaylightTime="0" <?= $selected == 7 ? 'selected ' : '' ?>value="7">(GMT+07:00) Bangkok, Hanoi, Jakarta</option>
				<option timeZoneId="63" gmtAdjustment="GMT+07:00" useDaylightTime="1" <?= $selected == 7 ? 'selected ' : '' ?>value="7">(GMT+07:00) Krasnoyarsk</option>
				<option timeZoneId="64" gmtAdjustment="GMT+08:00" useDaylightTime="0" <?= $selected == 8 ? 'selected ' : '' ?>value="8">(GMT+08:00) Beijing, Chongqing, Hong Kong, Urumqi</option>
				<option timeZoneId="65" gmtAdjustment="GMT+08:00" useDaylightTime="0" <?= $selected == 8 ? 'selected ' : '' ?>value="8">(GMT+08:00) Kuala Lumpur, Singapore</option>
				<option timeZoneId="66" gmtAdjustment="GMT+08:00" useDaylightTime="0" <?= $selected == 8 ? 'selected ' : '' ?>value="8">(GMT+08:00) Irkutsk, Ulaan Bataar</option>
				<option timeZoneId="67" gmtAdjustment="GMT+08:00" useDaylightTime="0" <?= $selected == 8 ? 'selected ' : '' ?>value="8">(GMT+08:00) Perth</option>
				<option timeZoneId="68" gmtAdjustment="GMT+08:00" useDaylightTime="0" <?= $selected == 8 ? 'selected ' : '' ?>value="8">(GMT+08:00) Taipei</option>
				<option timeZoneId="69" gmtAdjustment="GMT+09:00" useDaylightTime="0" <?= $selected == 9 ? 'selected ' : '' ?>value="9">(GMT+09:00) Osaka, Sapporo, Tokyo</option>
				<option timeZoneId="70" gmtAdjustment="GMT+09:00" useDaylightTime="0" <?= $selected == 9 ? 'selected ' : '' ?>value="9">(GMT+09:00) Seoul</option>
				<option timeZoneId="71" gmtAdjustment="GMT+09:00" useDaylightTime="1" <?= $selected == 9 ? 'selected ' : '' ?>value="9">(GMT+09:00) Yakutsk</option>
				<option timeZoneId="72" gmtAdjustment="GMT+09:30" useDaylightTime="0" <?= $selected == 9.5 ? 'selected ' : '' ?>value="9.5">(GMT+09:30) Adelaide</option>
				<option timeZoneId="73" gmtAdjustment="GMT+09:30" useDaylightTime="0" <?= $selected == 9.5 ? 'selected ' : '' ?>value="9.5">(GMT+09:30) Darwin</option>
				<option timeZoneId="74" gmtAdjustment="GMT+10:00" useDaylightTime="0" <?= $selected == 10 ? 'selected ' : '' ?>value="10">(GMT+10:00) Brisbane</option>
				<option timeZoneId="75" gmtAdjustment="GMT+10:00" useDaylightTime="1" <?= $selected == 10 ? 'selected ' : '' ?>value="10">(GMT+10:00) Canberra, Melbourne, Sydney</option>
				<option timeZoneId="76" gmtAdjustment="GMT+10:00" useDaylightTime="1" <?= $selected == 10 ? 'selected ' : '' ?>value="10">(GMT+10:00) Hobart</option>
				<option timeZoneId="77" gmtAdjustment="GMT+10:00" useDaylightTime="0" <?= $selected == 10 ? 'selected ' : '' ?>value="10">(GMT+10:00) Guam, Port Moresby</option>
				<option timeZoneId="78" gmtAdjustment="GMT+10:00" useDaylightTime="1" <?= $selected == 10 ? 'selected ' : '' ?>value="10">(GMT+10:00) Vladivostok</option>
				<option timeZoneId="79" gmtAdjustment="GMT+11:00" useDaylightTime="1" <?= $selected == 11 ? 'selected ' : '' ?>value="11">(GMT+11:00) Magadan, Solomon Is., New Caledonia</option>
				<option timeZoneId="80" gmtAdjustment="GMT+12:00" useDaylightTime="1" <?= $selected == 12 ? 'selected ' : '' ?>value="12">(GMT+12:00) Auckland, Wellington</option>
				<option timeZoneId="81" gmtAdjustment="GMT+12:00" useDaylightTime="0" <?= $selected == 12 ? 'selected ' : '' ?>value="12">(GMT+12:00) Fiji, Kamchatka, Marshall Is.</option>
				<option timeZoneId="82" gmtAdjustment="GMT+13:00" useDaylightTime="0" <?= $selected == 13 ? 'selected ' : '' ?>value="13">(GMT+13:00) Nuku'alofa</option>
			</select>
			<?php
		}
	}