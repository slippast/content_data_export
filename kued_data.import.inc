<?php
/**
 * Build the form
 * Flush and reimport the program guide data.
 */
function kued_data_refresh(){
	$form['refresh'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Refresh the ProTrack data.'),
	  '#weight' => 5,
	  '#collapsible' => FALSE,
	  '#collapsed' => FALSE,	
	);
	$form['refresh']['details'] = array(
		'#markup' => t('<h3>Instructions:</h3><p><strong>Import each file individually</strong>. For some reason the files may not import on the first few tries. After extensive troubleshooting I never found the problem.  So if you attempt the import and the progress bar finishes almost immediately it\'s safe to assume that the import failed.  Just push the button again until it works.  You\'ll know it \'took\' if it you see the counter below the progress bar showing the batch total increasing.</p>'),
	);
	$form['refresh']['airlist'] = array(
		'#type' => 'submit',
		'#value' => t('Airlist'),
	);
  $form['refresh']['series'] = array(
		'#type' => 'submit',
		'#value' => t('Series'),
	);
  $form['refresh']['episode'] = array(
		'#type' => 'submit',
		'#value' => t('Episode'),
	);
	$form['refresh']['report'] = array(
		'#markup' => t('<p><em>Please Note:</em> This data is only used for generating this report.  This will not affect the website content in anyway.</p>'),
	);
	$form['refresh_all'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Refresh all the ProTrack data one set at a time.'),
	  '#weight' => 5,
	  '#collapsible' => FALSE,
	  '#collapsed' => FALSE,	
	);
	$form['refresh_all']['warning'] = array(
		'#markup' => t('<p>Pushing this button will flush and refresh the program guide tables with the most current data. This method has proven unreliable.</p>'),
  );
	$form['refresh_all']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Refresh All'),
	);
	return $form;
}

/**
 * Form submit.
 */
function kued_data_refresh_submit(&$form, $form_state){
  $item = $form_state['values']['op'];
	kued_data_refresh_collect($item);
}

/**
 * What to do with the form submission
 */
function kued_data_refresh_collect($item) {
  $redirect_path = 'admin/config/content/kued/data/refresh';
	$file_path = drupal_realpath('private://');
	$airlist = "airlist.txt";
	$airlist_location = file_create_url($file_path . '/' . $airlist);
	$series = "series.txt";
	$series_location = file_create_url($file_path . '/' . $series);
	$episode = "episode.txt";
	$episode_location = file_create_url($file_path . '/' . $episode);

  // define batch array structure
  $batch = array(
    'title' => t('Purge ProTrack data and Refresh'),
    'operations' => array(),
		'init_message' => t('Starting...'),
		'progress_message' => t('Batch @current out of @total'),
		'error_message' => t('An error occurred and some or all of the batch has failed.'),
		//'finished' => 'refresh_finished',
		'file' => drupal_get_path('module', 'kued_data') . '/kued_data.import.inc'
  );

  // Based on the user's submission check for errors and build the batch.
  if($item == 'Refresh All') {
    $file_check_1 = kued_data_protrack_check('Airlist', $airlist_location);
    $file_check_2 = kued_data_protrack_check('Series', $series_location);
    $file_check_3 = kued_data_protrack_check('Episode', $episode_location);
    // Check for errors
    if($file_check_1 != 0 || $file_check_2 != 0 || $file_check_2 != 0) {
      $batch['operations'][] = array('kued_data_refresh_empty', array('all'));
      $batch['operations'][] = array('kued_data_refresh_import', array($airlist_location));
      $batch['operations'][] = array('kued_data_refresh_import', array($series_location));
      $batch['operations'][] = array('kued_data_refresh_import', array($episode_location));
      $file_check = 1;
    } else {
      drupal_set_message(t('Protrack refresh failed!'), 'error');
      watchdog('KUED Data', 'Protrack refresh failed!', WATCHDOG_ALERT);
    }

  } elseif($item == 'Airlist') {
     $file_check = kued_data_protrack_check($item, $airlist_location);
     if($file_check == 1) {
       $batch['operations'][] = array('kued_data_refresh_empty', array('airlist'));
       $batch['operations'][] = array('kued_data_refresh_import', array($airlist_location)); 
     }
  } elseif($item == 'Series') {
     $file_check = kued_data_protrack_check($item, $series_location);
     if($file_check == 1) {
       $batch['operations'][] = array('kued_data_refresh_empty', array('series'));
       $batch['operations'][] = array('kued_data_refresh_import', array($series_location)); 
     }
  } elseif($item == 'Episode') {
     $file_check = kued_data_protrack_check($item, $episode_location);
     if($file_check == 1) {
       $batch['operations'][] = array('kued_data_refresh_empty', array('episode'));
       $batch['operations'][] = array('kued_data_refresh_import', array($episode_location)); 
     }
  }

  if($file_check == 1) {
    // set batch
    batch_set($batch);
  }
}

/**
 * We need to do a file check to see if 
 * #1 the file exists and #2 it's readable
 */
function kued_data_protrack_check($item, $file) {
  $check = 0;
  if (file_destination($file, FILE_EXISTS_ERROR)) {
    drupal_set_message(t('Protrack @item file does not exist! The ProTrack data could not be imported.', array('@item' => $item)), 'error');
    watchdog('KUED Data', 'Protrack @item file does not exist! The ProTrack data could not be imported.', array('@item' => $item), WATCHDOG_ALERT);
    return $check;
  } else {
    $check = 1;
  }
  if (!is_readable($file)) {
    drupal_set_message(t('Protrack @item file is not readable by Drupal! The ProTrack data could not be imported.', array('@item' => $item)), 'error');
    watchdog('KUED Data', 'Protrack @item file is not readable by Drupal! The ProTrack data could not be imported.', array('@item' => $item), WATCHDOG_ALERT);
    return $check;
  } else {
    $check = 1;
  }
  return $check; 
}

/**
 * Empty the protrack tables
 */
function kued_data_refresh_empty($file = '', &$context = '') {
  if($file == 'all') {
    if(db_query("TRUNCATE TABLE protrack_airlist")) {
     watchdog('KUED Data', 'Protrack Airlist table successfully emptied.');
    } else {
     watchdog('KUED Data', 'Protrack Airlist table was NOT emptied!', WATCHDOG_ALERT);
    }
    if(db_query("TRUNCATE TABLE protrack_series")) {
     watchdog('KUED Data', 'Protrack Series table successfully emptied.');
    } else {
     watchdog('KUED Data', 'Protrack Series table was NOT emptied!', WATCHDOG_ALERT);
    }
    if(db_query("TRUNCATE TABLE protrack_episode")) {
     watchdog('KUED Data', 'Protrack Episode table successfully emptied.'); 
    } else {
     watchdog('KUED Data', 'Protrack Episode table was NOT emptied!', WATCHDOG_ALERT);
    }
  } elseif($file == 'airlist') {
    if(db_query("TRUNCATE TABLE protrack_airlist")) {
     watchdog('KUED Data', 'Protrack Airlist table successfully emptied.');
    } else {
     watchdog('KUED Data', 'Protrack Airlist table was NOT emptied!', WATCHDOG_ALERT);
    }
  } elseif($file == 'series') {
    if(db_query("TRUNCATE TABLE protrack_series")) {
     watchdog('KUED Data', 'Protrack Series table successfully emptied.');
    } else {
     watchdog('KUED Data', 'Protrack Series table was NOT emptied!', WATCHDOG_ALERT);
    }
  } elseif($file == 'episode') {
    if(db_query("TRUNCATE TABLE protrack_episode")) {
     watchdog('KUED Data', 'Protrack Episode table successfully emptied.'); 
    } else {
     watchdog('KUED Data', 'Protrack Episode table was NOT emptied!', WATCHDOG_ALERT);
    }
  }
}

/**
 * Reload the protrack data
 */
function kued_data_refresh_import($data_file, &$context){
	if (empty($context['sandbox'])) {
		$context['sandbox']['progress'] = 0;
		$context['sandbox']['max'] = count(file($data_file));
		$context['sandbox']['file_pointer_position'] = '';
		}
	// define batch limit
	$batch_limit = 100;
	// assume the batch process has not completed
	$context['finished'] = 0;
	// open the file for reading
	$file_handle = fopen($data_file, 'r');

	//Check the file type so I can do the correct function
	$file_type_check1 = strpos($data_file, 'series'); // Files is Series
		if($file_type_check1 !== FALSE) {
      $file_type = 'series';
		}
	$file_type_check2 = strpos($data_file, 'episode'); // Files is Episode
		if($file_type_check2 !== FALSE) {
      $file_type = 'episode';
		}
	$file_type_check3 = strpos($data_file, 'airlist'); // File is Airlist
		if($file_type_check3 !== FALSE) {
      $file_type = 'airlist';
		}

  // check if file pointer position exists in the sandbox, and jump to location in file
  if ($context['sandbox']['file_pointer_position']) {
	  fseek($file_handle, $context['sandbox']['file_pointer_position']);
  }
  // loop through the file and stop at batch limit
  for ($i = 0; $i < $batch_limit; $i++) {
    // get file line as csv
    $file_data_row = fgetcsv($file_handle, 0, "|");

    // Run the function to import the array
    if(is_array($file_data_row)) {
			// Get the file type
			if($file_type == 'series') {
					// Skip the first line
					if(is_numeric($file_data_row[0])) {
						kued_data_series_protrack_single($file_data_row);
					}
				} elseif($file_type == 'episode') {
					// Skip the first line
					if(is_numeric($file_data_row[1])) {
						kued_data_episode_protrack_single($file_data_row);
					}
				} elseif($file_type == 'airlist') {
					// Skip the first line
					if(is_numeric($file_data_row[1])) {
						kued_data_airlist_protrack_single($file_data_row);
					}
				}
			$context['sandbox']['progress']++;
		}
	
		// Show progress
		if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
			$context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
			$context['message'] = t('Now processing %v', array('%v' => $context['sandbox']['progress']));
		}

		// retain current file pointer position
		$context['sandbox']['file_pointer_position'] = ftell($file_handle);

    // check for EOF
    if (feof($file_handle)) {
      // complete the batch process
      $context['finished'] = 1;
			drupal_set_message(t('<strong>@v</strong> @t Records Added', array('@v' => $context['sandbox']['progress'], '@t' => $file_type)));

      // end loop
      break;
    }
  }
}

/**
 * Import Airlist items
 */
function kued_data_airlist_protrack_single($row){
	//Filter out the UEN content
	$channel = $row['5'];
	if($channel != 'KUEN-DT' && $channel != 'MHZ' && $channel != 'FNX') {
    $airlist_row = array(
      'fulldate' => drupal_convert_to_utf8(trim($row['0']), 'ISO-8859-1'),
      'series_id' => drupal_convert_to_utf8(trim($row['1']), 'ISO-8859-1'),
      'program_id' => drupal_convert_to_utf8(trim($row['2']), 'ISO-8859-1'),
      'version_id' => drupal_convert_to_utf8(trim($row['3']), 'ISO-8859-1'),
      'rebroadcast' => drupal_convert_to_utf8(trim($row['4']), 'ISO-8859-1'),
      'channel' => drupal_convert_to_utf8(trim($row['5']), 'ISO-8859-1'),
      );
    db_insert('protrack_airlist')
      ->fields($airlist_row)
      ->execute();
   }
}

/**
 * Import Series items
 */
function kued_data_series_protrack_single($row){
	$row[2] = drupal_convert_to_utf8(trim($row[2]), 'ISO-8859-1');

  if(isset($row[5])) {
    $series_pgm_type = trim($row[5]);
  } else {
    $series_pgm_type = '';
  }

	$insert = db_insert('protrack_series')
	->fields(array(
		'series_id' => drupal_convert_to_utf8(trim($row[0]), 'ISO-8859-1'),
		'series_code' => drupal_convert_to_utf8(trim($row[1]), 'ISO-8859-1'),
		'series_title' => $row[2],
		'series_description' => drupal_convert_to_utf8(trim($row[3]), 'ISO-8859-1'),
		'series_url' => drupal_convert_to_utf8(trim($row[4]), 'ISO-8859-1'),
		'series_pgm_type' => $series_pgm_type,
	))
	->execute();
}

/**
 * Import Episode items
 */
function kued_data_episode_protrack_single($row){
	$row[5] = drupal_convert_to_utf8(trim($row[5]), 'ISO-8859-1');
	$row[23] = trim($row[23]);
	$row[24] = trim($row[24]);

	if(empty($row[23])){
		$row[23] = date('m/d/Y',strtotime('now + 30 days')); //06/30/2016
	}
	if(empty($row[24])){
		$row[24] = date('m/d/Y',strtotime('now - 30 days')); //06/30/2016
	}

	if(empty($row[23]) || empty($row[24])){
		watchdog('KUED Data', 'No date for Episode: %title (%eid) - entry skipped', array('%eid' => $row['1'], '%title'=> $row[5]));
	} else {
	$insert = db_insert('protrack_episode')
	->fields(array(
		'series_id' => drupal_convert_to_utf8(trim($row[0]), 'ISO-8859-1'),
		'program_id' => drupal_convert_to_utf8(trim($row[1]), 'ISO-8859-1'),
		'version_id' => drupal_convert_to_utf8(trim($row[2]), 'ISO-8859-1'),
		'episode_len' => drupal_convert_to_utf8(trim($row[3]), 'ISO-8859-1'),
		'episode_num' => drupal_convert_to_utf8(trim($row[4]), 'ISO-8859-1'),
		'episode_title' => $row[5],
		'episode_guide' => drupal_convert_to_utf8(trim($row[6]), 'ISO-8859-1'),
		'episode_desc' => drupal_convert_to_utf8(trim($row[7]), 'ISO-8859-1'),
		'episode_url' => drupal_convert_to_utf8(trim($row[8]), 'ISO-8859-1'),
		'episode_rating' => drupal_convert_to_utf8(trim($row[9]), 'ISO-8859-1'),
		'episode_language' => drupal_convert_to_utf8(trim($row[10]), 'ISO-8859-1'),
		'episode_caption' => drupal_convert_to_utf8(trim($row[11]), 'ISO-8859-1'),
		'episode_dvs' => drupal_convert_to_utf8(trim($row[12]), 'ISO-8859-1'),
		'episode_stereo' => drupal_convert_to_utf8(trim($row[13]), 'ISO-8859-1'),
		'episode_hdtv' => drupal_convert_to_utf8(trim($row[14]), 'ISO-8859-1'),
		'episode_letterbox' => drupal_convert_to_utf8(trim($row[15]), 'ISO-8859-1'),
		'episode_source' => drupal_convert_to_utf8(trim($row[16]), 'ISO-8859-1'),
		'episode_topic1' => drupal_convert_to_utf8(trim($row[17]), 'ISO-8859-1'),
		'episode_topic1_t' => drupal_convert_to_utf8(trim($row[18]), 'ISO-8859-1'),
		'episode_topic2' => drupal_convert_to_utf8(trim($row[19]), 'ISO-8859-1'),
		'episode_topic2_t' => drupal_convert_to_utf8(trim($row[20]), 'ISO-8859-1'),
		'episode_sdef' => drupal_convert_to_utf8(trim($row[21]), 'ISO-8859-1'),
		'episode_sdef_t' => drupal_convert_to_utf8(trim($row[22]), 'ISO-8859-1'),
		'rits_start' => drupal_convert_to_utf8(trim($row[23]), 'ISO-8859-1'),
		'rits_end' => drupal_convert_to_utf8(trim($row[24]), 'ISO-8859-1'),
		'keywords' => drupal_convert_to_utf8(trim($row[25]), 'ISO-8859-1'),
		'episode_genre' => drupal_convert_to_utf8(trim($row[26]), 'ISO-8859-1'),
		'pack_type' => drupal_convert_to_utf8(trim($row[27]), 'ISO-8859-1')
	))
	->execute();
	}
}
