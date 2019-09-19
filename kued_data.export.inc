<?php

function kued_data_export_program($data) {
	switch ($data['format']){
		case 'seven':
			$collection = kued_data_collect_seven($data);
			$output = kued_data_export_seven($collection);
			$directory = 'kued_data/seven';
			$directory_uri = file_build_uri($directory);
			if(file_prepare_directory($directory_uri)) {
				$name = file_build_uri($directory.'/'.$collection['name']);
				$collection_location = file_unmanaged_save_data($collection['html'], $name, $replace = FILE_EXISTS_REPLACE);
			}
		break;
		case 'grid';
			$collection = kued_data_collect_seven($data);
			$output = kued_data_export_grid($collection);
			$directory = 'kued_data/grid';
			$directory_uri = file_build_uri($directory);
			if(file_prepare_directory($directory_uri)) {
				$name = file_build_uri($directory.'/'.$collection['name']);
				$collection_location = file_unmanaged_save_data($collection['html'], $name, $replace = FILE_EXISTS_REPLACE);
			}
		break;
		case 'lyric';
			$collection = kued_data_collect_seven($data);
			$output = kued_data_export_lyric($collection);
			$directory = 'kued_data/lyric';
			$directory_uri = file_build_uri($directory);

			switch($data['form']) {
				case 'document':
					$name = "LYRIC-SerList_Made-" . date('M-d-Y') . ".xls";
				break;
				case 'web':
				default:
					$name = "LYRIC-SerList_Made-" . date('M-d-Y') . ".htm";
				break;
			}
			
			if(file_prepare_directory($directory_uri)) {
				$name = file_build_uri($directory.'/'.$name);
				$collection_location = file_unmanaged_save_data($output, $name, $replace = FILE_EXISTS_REPLACE);
			}
			//dsm($collection);
		break;
		case 'outgoing';
			$collection = kued_data_collect_seven($data);
			$output = kued_data_export_outgoing($collection);
			$directory = 'kued_data/lyric';
			$directory_uri = file_build_uri($directory);

			switch($data['form']) {
				case 'document':
					$name = strtoupper(date('M')) . "_KUED_HD_" . date('Y') . ".doc";
				break;
				case 'web':
				default:
					$name = strtoupper(date('M')) . "_KUED_HD_" . date('Y') . ".htm";						
				break;
				}

			if(file_prepare_directory($directory_uri)) {
				$name = file_build_uri($directory.'/'.$name);
				$collection_location = file_unmanaged_save_data($output, $name, $replace = FILE_EXISTS_REPLACE);
			}
			//dpm($collection);
		break;
	}
	//dsm($collection);	
	if(isset($collection_location)) {
		return $collection_location;
	}
/*
	if(isset($collection_location_alt)){
		return $collection_location_alt;
	}
*/
}


function kued_data_export_seven($collection) {
	$output = '';
/*
	$output .= '
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
		<html xmlns="http://www.w3.org/1999/xhtml">		
		<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>KUED Data Export | Style: ' . strtoupper($data['format']) . ' | ' . date('F j, Y, g:i a', strtotime('now')) .'</title>
		</head>
		<body>
		';
*/

	return $output;
}

function kued_data_export_grid($collection) {
	$output = '';
	$output .= '
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
		<html xmlns="http://www.w3.org/1999/xhtml">		
		<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>KUED Data Export | Style: ' . strtoupper($data['format']) . ' | ' . date('F j, Y, g:i a', strtotime('now')) .'</title>
		</head>
		<body>
		';

	return $output;
}

function kued_data_export_lyric($collection) {
	$output = '';
	foreach($collection['months'] as $month) {
		//dsm($month);
		foreach($month['weeks'] as $week) {
			$output .= "\n" . date('l, F jS', $week['timestamp']) . "\n";
			//dsm($week);
			foreach($week['days'] as $day) {
				//dsm($day);
				foreach($day as $show){
					//dsm($show);
						$output .= "" . $show['fulldate'];
						$output .= "\t" . date('g:i a', strtotime($show['fulldate']));
						$output .= " \t";
						if (!empty($show['series_title'])) {
							$output .= $show['series_title'];
						} else {
							$output .= $show['episode_title'];
						}
						$output .= "\n";
						$channel = $show['channel'];
				}
			}
		}
	}

//dsm($output);
/*
	if ($output == "") { 
		$output = "\n(0) Records Found!\n";
	} else {
		header("Cache-Control: ");// leave blank to avoid IE errors
		header("Pragma: ");// leave blank to avoid IE errors
		header("Content-type: application/octet-stream");
	//	header("Content-Disposition: attachment; filename=\"$file\"");
	//	header("Content-length:".(string)(filesize($filename)));
	//	header("Content-type: application/x-msdownload");
		header('Content-type: application/ms-excel');
		header("Content-Disposition: attachment; filename=LYRIC-SerList_Ch({$show['channel']})_Made(" . date('M-d-Y') . ").xls"); 
	//	header("Pragma: no-cache"); 
		header("Expires: 0"); 
	//	print "$header\n$data";
		print trim($output);
		$output = close();
	}
*/
	return $output;
}



function kued_data_export_outgoing($collection) {
	//dpm($collection);
	$output = '';
	$output .= '<html>';
	$output .= '<meta http-equiv=\"Content-Type\" content=\"text/html; charset=Windows-1252\">';
	$output .= '<style>body { font-family:Arial, Helvetica, sans-serif; }</style>';
	$output .= '<body>';

	foreach($collection['months'] as $month_key => $month) {
		//dsm($month);
		$output .= 'KUED Listings for: <strong>' . date('F Y', strtotime($month_key)) . '</strong><br />';
		foreach($month['weeks'] as $week) {
			//dsm($week);
			foreach($week['days'] as $day_timestamp => $day) {
				//dsm($day);

				$output .= '<br /><br /><strong>' . date('jS', $day_timestamp) . '&nbsp;&nbsp;&nbsp;&nbsp;' . date('l', $day_timestamp) . '</strong><br /><hr /><br />';
				foreach($day as $show){
					$fulldate_unix = strtotime($show['fulldate']);
					$fulldate = time_fix(date('g:i', $fulldate_unix));
					$output .= $fulldate . date(' a', $fulldate_unix);
					$output .= "&nbsp;&nbsp;&nbsp;";

					if (!empty($show['episode_title'])) {
						$title = $show['series_title'] . ': ' . $show['episode_title'];
					} else {
						$title = $show['series_title'];
					}
					$output .= '<strong>' . $title . '</strong>';
					$output .= "<br />";

					if($show['episode_source'] == 'KUED'){
						$episode_guide = trim($show['episode_guide']);
						if(!empty($episode_guide)){
							//$output .= "<p>";
							$output .= $episode_guide;
							$output .= "<br />";
						}
					}

					$episode_num = trim($show['episode_num']);
					$episode_dvs = trim($show['episode_dvs']);
					// Start the second line
					if(!empty($episode_num)) {
						$episode_num = 'Episode #: ' . $episode_num;
					} else {
						$episode_num = '';
					}
					if(!empty($show['episode_source'])) {
						$episode_source = ' | Distributor: ' . $show['episode_source'];
					} else {
						$episode_source = '';
					}
					if(!empty($show['episode_caption'])) {
						$episode_caption = ' | CC';
					} else {
						$episode_caption = '';
					}
					if(!empty($show['episode_stereo'])) {
						$episode_stereo = ' | ' . $show['episode_stereo'];
					} else {
						$episode_stereo = '';
					}
					if(!empty($episode_dvs)) {
						$episode_dvs =  ' | ' . $episode_dvs;
					} else {
						$episode_dvs = '';
					}
					$output .= $episode_num . $episode_source . $episode_caption . $episode_stereo . $episode_dvs;
					$output .= '<br /><br />';

				}
				/*
				if(date('l', $day_timestamp) == 'Saturday'){
					$output .= 'KUED HD Channel 7.1<br />';
					$output .= '<strong>Listings for the week beginning ' . date('l, F jS, Y', $week['timestamp']) . '</strong><br />';
					$output .= 'If you have questions about KUED\'s listings, please contact Elizabeth Renda at (801) 581-3065 or <a href="mailto:erenda@kued.org">lrenda@kued.org</a>.<br /><br />';
				}
				*/
			}
		}
	}
	$output .= '</body>';
	$output .= '</html>';
	return $output;
}


// Private function to build the big array of data to export
function kued_data_collect_seven($data) {
	module_load_include('inc', 'kued_data', 'kued_data.functions');
	$one_day = 86400; // Number of seconds in a day

	$document = '';

	if($data['format'] == 'seven' || $data['format'] == 'grid') {
	$document .= '
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
		<html xmlns="http://www.w3.org/1999/xhtml">
		
		<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>KUED Data Export | Style: ' . strtoupper($data['format']) . ' | ' . date('F j, Y, g:i a', strtotime('now')) .'</title>
		</head>
		
		<body>
		';
	}
//dpm($data);
	$c = 1;
	// Build framework for the month search
	// must comply with the week search for data organization
	if($data['time_frame'] == 'months') {
		$data['weeks'] = array(); // Empty this variable because we'll reuse it now
		foreach($data['months'] as $month) {
			if($month != 0) {

				// First check the count to determine the number of cycles (days in the week)
				$document .= "<h1 style='font-size:1.4em;'>Showing: " . date('M Y', $month) . " | Channel: " .  $data['channel'] . "</h2>";

				if($data['format'] == 'seven' || $data['format'] == 'grid'){
					$document .= "<h3 style='font-size:1.2em;'>Format: " . strtoupper($data['format']) . "</h3><hr />";
				}

				$month_data['month'] = date('F', $month);
				$month_data['year'] = date('Y', $month);
				$month_data['total_days'] = date('t', $month);
				$month_data['days_remaining'] = date('t', $month);
				$month_data['first_day'] = date('Y-m-d', $month);
				$month_data['last_day'] = date('Y-m-d', strtotime('last day of ' . $month_data['month'] . ' ' . $month_data['year']));
				$month_data['first_day_ts'] = $month;
				$month_data['last_day_ts'] = strtotime('last day of ' . $month_data['month'] . ' ' . $month_data['year']);
				$month_data['last_sunday'] = strtotime('last sunday of ' . $month_data['month'] . ' ' . $month_data['year']);
				$month_data['begin_day_of_week'] = date('w', $month)+1;
				$month_data['end_day_of_week'] = date('w', strtotime($month_data['last_day']))+1;

//dpm($month_data);
				// Work out the range of days for the first week
				if($month_data['begin_day_of_week'] != 7) {
					$month_data['begin_range'] = ($month_data['begin_day_of_week'] - 7) * (-1);
				} else {
					$month_data['begin_range'] = 7;
				}
				/*
				// Work out the range of days for the Last week				
				if($month_data['end_day_of_week'] != 7) {
					$month_data['end_range'] = ($month_data['end_day_of_week'] - 7) * (-1);
				} else {
					$month_data['end_range'] = 7;
				}
				*/
				$month_data['end_range'] = $month_data['end_day_of_week']+1;

				// Build a weekly breakdown to send to the next function
				$d = $month_data['begin_day_of_week'];
				$i = 1;
				while($i <= $month_data['total_days']) {

					$month_data['current_day'][$i] = $d;
					if($i == 1) {
            //dpm(strtotime($month_data['month'] . ' ' . $i . ' ' . $month_data['year']));
						$data['weeks'][] = strtotime($month_data['month'] . ' ' . $i . ' ' . $month_data['year']);
					}
					if($i != 1){
						if($d == 1){
              //dpm(strtotime($month_data['month'] . ' ' . $i . ' ' . $month_data['year']));
							$data['weeks'][] = strtotime($month_data['month'] . ' ' . $i . ' ' . $month_data['year']);
						}
					}

					//$data['weeks']['current'][$i] = strtotime($month_data['month'] . ' ' . $i . ' ' . $month_data['year']);
					$month_data['current'][$i] = strtotime($month_data['month'] . ' ' . $i . ' ' . $month_data['year']);
					$i++;
					
					if($d >= 7) {
						$d = 1;
						$c++;
					} else {
						$data['count'] = $c;
						$month_data['count'] = $c;
						$d++;
					}
				}
			}
		}
		//dpm($month_data);
	// If the user selected weeks just render the entire week...
	} elseif($data['time_frame'] == 'weeks') {
		// Weeks is set, choose the default number of days to cycle through
		//$data['begin_range'] = 7;
		//$data['end_range'] = 7;
		$month_data['begin_day_of_week'] = 1;
		$month_data['end_day_of_week'] = 1;
		$month_data['begin_range'] = 7;
		$month_data['end_range'] = 7;
		// We need to total up the number of weeks been exported
		foreach($data['weeks'] as $week) {
			if($week != 0){
				$data['count'] = $c;
				$month_data['count'] = $c;
			}
			$c++;
		}
	}

	// This is the big array that we're going to return for formatting purposes
	$collection = array();
	$z = 1; // range counter
	$d = 1; // outgoing counter
	// Everything is broken into weeks, now build the export
	foreach($data['weeks'] as $week) {

		if($week != 0){ // if week not empty then spin it
			// First check the count to determine the number of cycles (days in the week)
			if($data['format'] == 'seven') {
				//Set the document and go
				$document .= "<h2 style='font-size:1.4em;'>" .  $data['channel'] . "</h2>";
				$document .= "<h3 style='font-size:1.2em;'>Listings for the week beginning " . date('l, F jS, Y', $week) . "</h3>";
			}
						
			// Set up some parameters here
			if($z == 1){
				$range = $month_data['begin_range'];
				$week_start = date('Y\WW', $week - ($one_day * ($range - 1))); // silly math to make this work
			} elseif($z == $data['count']) {
				$range = $month_data['end_range'];
				$week_start = date('Y\WW', $week);
			} else {
				$range = 7;
				$week_start = date('Y\WW', $week);
			}
			//dpm('range: '.$range);
			$z++;

			// Get the current day (first day of the week) for the 'weeks' view
			if($data['time_frame'] == 'weeks') {
				$current_day_ts = $week;
			}
			$current_month = date('M-Y', $week);

			// Add to the big array that we're going to return to the build function
			$collection['months'][$current_month]['weeks'][$week_start]['timestamp'] = $week;
			$collection['months'][$current_month]['weeks'][$week_start]['channel'] = $data['channel'];
			$collection['months'][$current_month]['weeks'][$week_start]['title'] = "Listings for the week beginning " . date('l, F jS, Y', $week);

			$i = 1;
			// iterate through the range of days in the week
			while($i <= $range) {
				//dpm('c: '.$c);
				//dpm('d: '.$d);
				#dpm('total_days: '.$month_data['total_days']);
				if($d > $month_data['total_days']){
					// burp
				} else {
					// Get current day timestamp (already built)
					if($data['time_frame'] == 'months') {
						$current_day_ts = $month_data['current'][$d];
						$d++;
					}
				}
				//dpm($i . ' :$i .... $range: ' . $range);
				$current_day = date('l F j Y, g:i a', $current_day_ts);
				//dpm($current_day_ts . ' | ' . $current_day);
				$week_day = date('l', $current_day_ts);
				$week_date = date('jS', $current_day_ts);
				// build the search parameters
				$search = array();
				switch($data['format']) {
				case 'outgoing':
					switch($week_day) {
						case 'Sunday':
							$search['week_day'] = FALSE;
							$search['day'] = $week_day;
							$search['date_stamp'] = $current_day_ts;
							$search['date_display'] = $current_day;
							if($d == 0){
								$search['begin'] = date('Y-m-d', $current_day_ts) . " 06:00:00";	// 6:00am "today"
								$d++;
							} else {
								$search['begin'] = date('Y-m-d', $current_day_ts) . " 00:00:00";	// 6:00am "today"
							}
								$search['end'] = date('Y-m-d', $current_day_ts) . " 24:00:00";		// 12:00pm "tomorrow"
						break;
						default:
							$search['week_day'] = FALSE;
							$search['day'] = $week_day;
							$search['date_stamp'] = $current_day_ts;
							$search['date_display'] = $current_day;
							$search['begin'] = date('Y-m-d', $current_day_ts) . " 00:00:00";	// 12:00am "today"
							$search['end'] = date('Y-m-d', $current_day_ts) . " 24:00:00";		// 12:00pm "tomorrow"
						break;
					}
				break;
				case 'lyric':
					$search['week_day'] = FALSE;
					$search['day'] = $week_day;
					$search['date_stamp'] = $current_day_ts;
					$search['date_display'] = $current_day;
					$search['begin'] = date('Y-m-d', $current_day_ts) . " 00:00:00";	// 12:00am "today"
					$search['end'] = date('Y-m-d', $current_day_ts) . " 24:00:00";		// 12:00pm "tomorrow"
				break;
				case 'grid':
					switch($week_day) {
						case 'Monday':
						case 'Tuesday':
						case 'Wednesday':
						case 'Thursday':
						case 'Friday':
							$search['week_day'] = TRUE;
							$search['day'] = $week_day;
							$search['date_stamp'] = $current_day_ts;
							$search['date_display'] = $current_day;
							$search['begin'] = date('Y-m-d', $current_day_ts) . " 19:00:00";	// 7:00pm "today"
              $search['end'] = date('Y-m-d', $current_day_ts) . " 22:50:00";		// 10:30am "tomorrow"
						break;
						case 'Saturday':
						case 'Sunday':
							$search['week_day'] = FALSE;
							$search['day'] = $week_day;
							$search['date_stamp'] = $current_day_ts;
							$search['date_display'] = $current_day;
							$search['begin'] = date('Y-m-d', $current_day_ts) . " 19:00:00";	// 7:00pm "today"
              $search['end'] = date('Y-m-d', $current_day_ts) . " 22:50:00";		// 10:30am "tomorrow"
						break;
					}
				break;
				case 'seven':
					switch($week_day) {
						case 'Monday':
						case 'Tuesday':
						case 'Wednesday':
						case 'Thursday':
						case 'Friday':
							$search['week_day'] = TRUE;
							$search['day'] = $week_day;
							$search['date_stamp'] = $current_day_ts;
							$search['date_display'] = $current_day;
							$search['begin'] = date('Y-m-d', $current_day_ts) . " 17:30:00";	// 5:30pm "today"
							$search['end'] = date('Y-m-d', $current_day_ts + $one_day) . " 03:00:00";		// 3:00am "tomorrow"
							// Highlight: 7:00pm "today" to 9:00pm "today"
						break;
						case 'Saturday':
						case 'Sunday':
							$search['week_day'] = FALSE;
							$search['day'] = $week_day;
							$search['date_stamp'] = $current_day_ts;
							$search['date_display'] = $current_day;
							$search['begin'] = date('Y-m-d', $current_day_ts) . " 06:00:00";	// 5:30pm "today"
							$search['end'] = date('Y-m-d', $current_day_ts + $one_day) . " 03:30:00";		// 3:00am "tomorrow"
							// Highlight: 6:00pm "today" to 9:00pm "today"
						break;
					}
				break;
				}


				$document .= '
<br /><br /><strong>'.$week_date.' &nbsp; &nbsp; &nbsp; &nbsp; '.$week_day.'</strong><br />
';

				// the big select that gets everything I'll need
				$query = "SELECT DISTINCT a.fulldate as fulldate, s.series_title, e.episode_title, e.episode_desc, e.episode_guide, e.episode_num, e.episode_source, e.episode_caption, e.episode_stereo, e.episode_dvs, a.channel FROM {protrack_airlist} AS a LEFT JOIN protrack_series AS s ON a.series_id = s.series_id LEFT JOIN protrack_episode AS e ON a.version_id = e.version_id WHERE (fulldate BETWEEN '':begin'' AND '':end'') AND a.channel = :channel ORDER BY fulldate ASC";
				$query_array = array(':channel' => $data['channel'], ':begin' => $search['begin'],':end' => $search['end']);
				$results = db_query($query, $query_array);

				// Here is where we build the main content
				while($result = $results->fetchAssoc()) {
					//dpm($result);
					// set some defaults
					$result['highlight'] = FALSE;
					$result['am'] = FALSE;
					$time = '';
					$title = '';
					// Fix some errors: trim off extra space
					$result['episode_source'] = trim($result['episode_source']);
					$result['series_title'] = trim($result['series_title']);
					$result['episode_title'] = trim($result['episode_title']);
					$result['episode_guide'] = reverse_html(t('@text', array('@text' => trim($result['episode_guide']))));
					$result['episode_desc'] = reverse_html(t('@text', array('@text' => trim($result['episode_desc']))));

					// Build the time
					$time = time_fix(date('g:i', strtotime($result['fulldate'])));

					// We need to turn on the highlight if needed
					$result_ts = strtotime($result['fulldate']);
					$current_hour = date('G', $result_ts);
/*
          dpm($result);
          dpm($result['fulldate']);
          dpm('title: ' . $result['episode_title']);
          dpm($time);
          dpm($result_ts);
          dpm($current_hour);
          dpm('---------');
*/
					if($search['week_day'] == TRUE){
						if($time == '12:00') {
							$result['am'] = TRUE;
							$time = $time.'A';
						}
						if($week_day == 'Friday' && $current_hour >= 20 && $current_hour <= 21){
							$result['highlight'] = TRUE;
						} elseif($current_hour >= 19 && $current_hour <= 21) {
							$result['highlight'] = TRUE;
						}
					} elseif($search['week_day'] == FALSE) {
						//if(preg_match("/06:00:00/", $result['fulldate']) || preg_match("/00:00:00/", $result['fulldate'])) {
						if($time == '6:00' || $time == '12:00') {
              if($current_hour < 12) {
                $result['am'] = TRUE;
                $time = $time.'A';
              }
						}
						if(preg_match("/12:00:00/", $result['fulldate'])) {
							$time = 'Noon';
						}
						if($week_day == 'Saturday' && $current_hour >= 18 && $current_hour <= 21){
							$result['highlight'] = TRUE;
						} elseif($week_day == 'Sunday' && $current_hour >= 18 && $current_hour <= 21) {
							$result['highlight'] = TRUE;
						}
					}

					// Build the title
					$title = title_fix($title, $result['series_title'], $result['episode_title'], $result['highlight'], $result['episode_source'], $data['format']);
          //dpm('title fix: ' . $title);

					// Create the body content
					$document .= '
<p style="margin-bottom:1em;">';
					$document .= '<strong>'.$time.'&#9;'.$title.'</strong>';

					// Create the description
					if($data['format'] == 'seven'){
						if($search['week_day'] == TRUE && $result['highlight'] == TRUE){
							if($data['description'] == 'long' && !empty($result['episode_desc'])) {
								$document .= '&nbsp;&nbsp;'.$result['episode_desc'];
							} elseif($data['description'] == 'short' && !empty($result['episode_guide'])) {
								$document .= '&nbsp;&nbsp;'.$result['episode_guide'];
							}
						} elseif ($search['week_day'] == FALSE && $result['highlight'] == TRUE) {
							if($data['description'] == 'long' && !empty($result['episode_desc'])) {
								$document .= '&nbsp;&nbsp;'.$result['episode_desc'];
							} elseif($data['description'] == 'short' && !empty($result['episode_guide'])) {
								$document .= '&nbsp;&nbsp;'.$result['episode_guide'];
							}						
						}
					}

					// insert the date and title into the array
					$result['time'] = $time;
					$result['title'] = $title;
					$collection['months'][$current_month]['weeks'][$week_start]['days'][$current_day_ts][] = $result;
/*
if(in_array('12:00A', $collection[$current_month][$week_start]['day'])) {
    dsm('Got it on: '.$current_day.' '.$title);
}
*/
					// End the body here
					$document .= '</p>
';
				}
				// keep rolling through the loop
				if($data['time_frame'] == 'weeks') {
					$current_day_ts = $current_day_ts + $one_day;
				}
				$i++;
				}

			//86400 day
			//604800 week
			//dpm($week_start);
			//dpm($current_day);
			if(!empty($current_day)){
			$display = date('F j, Y, g:i a', strtotime($current_day));
			//dsm($display);
			}
		}
	}

	if($data['format'] == 'seven' || $data['format'] == 'grid'){
		$document .= '</body></html>';
	}
	$collection['html'] = $document;
	$collection['name'] = 'export_' . $data['channel'] . '_' . strtoupper($data['format']) . '_' . strtotime($current_day) . '.htm';

	return $collection;
}


// Private function to build the titles
function title_fix($title, $series_title, $episode_title, $highlight, $source, $format){
	module_load_include('inc', 'kued_data', 'kued_data.functions');
	// Fix the series title
	$series_title = t('@series_title', array('@series_title' => $series_title));
	$series_title = kued_data_fix_text(kued_data_fix_title(reverse_html(t($series_title))));

	// Fix the episode title
	$episode_title = t('@episode_title', array('@episode_title' => $episode_title));
	$episode_title = reverse_html(kued_data_fix_text($episode_title));

	// Search for series which should always include the episode title
	$fix = title_fix_filter($series_title);
	if($format == 'seven'){
		if($fix == TRUE || $highlight == TRUE || $source == "KUED"){
			if (!empty($series_title)) {
				$title .= $series_title;
			}
			if (!empty($episode_title)) {
				$title .= ": " . $episode_title;
			}		
		} else {
			$title .= $series_title;
		}
	} elseif($format == 'grid') {
		$title .= $series_title;
	}
	// add a character for the local kued productions
	if($source == "KUED"){
		$title = '7 '.$title;
	}
	return $title;
}

// check the title
// should I move this to the DB? not right now
function title_fix_filter($series_title) {
	$haystack = array(
		'POV',
		'NOVA',
		'Nature',
		'Frontline',
		'Masterpiece',
		'Globe Trekker',
		'Independent Lens',
		'American Masters',
		'Great Performances',
		'Austin City Limits',
		'American Experience',
		'In Performance at the White House',
		'Constitution USA with Peter Sagal',
		'Live From Lincoln Center',
		'Secrets of the Dead',
		'History Detectives',
		'Antiques Roadshow',
		'NOVA scienceNOW',
		'PBS Arts',
	);
	if(in_array($series_title, $haystack)) {
		return TRUE;
	}
}

// Private function to fix the minutes that are off
function time_fix($number){
//dpm($number);
	// Make an array
	$number = explode(':', $number);
	// Granular to 5 minutes
	if($number[1] == '00' || $number[1] == '01' || $number[1] == '02' || $number[1] == '03') {
		$number[1] = '00';
	} elseif($number[1] == '04' || $number[1] == '05' || $number[1] == '06') {
		$number[1] = '05';
	} elseif($number[1] == '07' || $number[1] == '08' || $number[1] == '09' || $number[1] == '10' || $number[1] == '11' || $number[1] == '12') {
		$number[1] = '10';
	} elseif($number[1] >= '13' && $number[1] <= '17') {
		$number[1] = '15';
	} elseif($number[1] >= '18' && $number[1] <= '23') {
		$number[1] = '20';
	} elseif($number[1] >= '24' && $number[1] <= '26') {
		$number[1] = '25';
	} elseif($number[1] >= '27' && $number[1] <= '33') {
		$number[1] = '30';
	} elseif($number[1] >= '34' && $number[1] <= '36') {
		$number[1] = '35';
	} elseif($number[1] >= '37' && $number[1] <= '43') {
		$number[1] = '40';
	} elseif($number[1] >= '44' && $number[1] <= '46') {
		$number[1] = '45';
	} elseif($number[1] >= '47' && $number[1] <= '53') {
		$number[1] = '50';
	} elseif($number[1] >= '54' && $number[1] <= '56') {
		$number[1] = '55';
	} elseif($number[1] >= '57' && $number[1] <= '60') {
		$number[1] = '60';
	}

  if($number[1] == '60') {
    $number[0] = $number[0] + 1;
    $number[1] = '00';
  }

/*
dpm($number);
	if($number[1] <= 05) {
	}
	if($number[1] <= 15) {
		$number[1] = '00';
	} elseif ($number[1] >= 16 && $number[1] <= 44){
		$number[1] = '30';
	} elseif ($number[1] >= 45) {
		$number[1] = '00';
		$number[0] = $number[0] + 1;
	}
	if(isset($number[2])){
		$number[2] = ':00';
	} else {
		$number[2] = '';
	}
	if(strlen($number[0]) < 2){
		//$number[0] = '0'.$number[0];
	}
	$number = $number[0].':'.$number[1].$number[2];
	*/

	// Rebuild the number
	$number = $number[0].':'.$number[1];
//dpm($number);
//dpm('----');
	return $number;
}









/*
function kued_data_build_seven_web($collection) {
	$document = array();
	$document['html'] = '';
	$document['html'] .= '<html><head></head><body>';
	$document['html'] .= '</body></html>';
	return $document;
}
function kued_data_build_seven_grid($collection) {
	$document = array();
	$document['html'] = '';
	$document['html'] .= '<html><head></head><body>';
	$document['html'] .= '</body></html>';
	return $document;
}
*/