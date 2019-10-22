<?php

// These functions clean up the messy kued_data text

/**
 * Function to clean the MS text that finds its way in here.
 */
function kued_data_fix_text($fixed_string) {
	$ms_bad_characters = array(chr(145), chr(146), chr(147), chr(148), chr(150), chr(151), chr(133)); // Bad boy
	$ms_good_characters = array("'", "'", '"', '"', '-', '--', '...'); // Much Better
	$fixed_string = str_replace($ms_bad_characters, $ms_good_characters, $fixed_string); // Replace the nasty stuff now
	// Send the fix back
	return $fixed_string;
	}

/**
 * Function to clean the nasty kued_data tags from the titles
 */
function kued_data_fix_title($fixed_string) {
	$bad_characters = array('{World}', '{Annen}'); // Bad boy
	$fixed_string = str_replace($bad_characters, '', $fixed_string); // Replace the nasty stuff now
	$fixed_string = trim($fixed_string);

	// Fix the inverted ', The'
	$the_fix = array(', The', ',The', ', the', ',the'); // Find ', The'
	foreach($the_fix as $value) {
		$the_fix_check = strpos($fixed_string, $value);
		if($the_fix_check !== FALSE) {
			$fixed_string = str_replace($value, '', $fixed_string);
			$fixed_string = 'The ' . $fixed_string;
			}
		}
	// Send the fix back
	return $fixed_string;
}
/**
 * Reverse HTML characters for insert
 */
function reverse_html($reverse) {
	$translation = get_html_translation_table(HTML_SPECIALCHARS, ENT_QUOTES);
	$translation = array_flip($translation);
	$fixed_string = strtr($reverse, $translation);
	// Not sure why I have to do this but it's not getting the single quotes any other way
	$second_fix = array("&#039;" => "'");
	$fixed_string = strtr($fixed_string, $second_fix);

	return $fixed_string;
}

/**
 * Function to clean the nasty kued_data tags from the copyright
 */
function kued_data_fix_copyright($fixed_string) {
	$bad_characters = array('Â'); // Bad boy
	$fixed_string = str_replace($bad_characters, '', $fixed_string); // Replace the nasty stuff now
	$fixed_string = trim($fixed_string);
	return $fixed_string;
}


/**
 * Now we use a couple of functions to format the Taxonomy Data because the stuff coming from ProTrack is ugly
 * Fix the taxonomy for Series entries
 */
function series_import_taxonomy_fix($series_program_type) {
	switch ($series_program_type) {
		case 'ADVENTURE/TRAVL':
		$series_program_type_formatted = "Adventure - Travel";
		break;
		
		case 'ARTS':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'CHILDREN':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'COMEDY':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'DO':
		$series_program_type_formatted = "Documentary";
		break;
		case 'DOCUMENTARY':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'DRAMA':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'ECONOMYBUSINES':
		$series_program_type_formatted = "Economy - Business";
		break;
		
		case 'HEALTH':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'HISTOR':
		$series_program_type_formatted = "History";
		break;
		
		case 'HISTORY':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'HOW-TO':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'I - T - V':
		$series_program_type_formatted = "I-T-V";
		break;
		
		case 'LIFESTYLE':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'MO':
		$series_program_type_formatted = "Movie";
		break;
		case 'MOVIE':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'NATURE':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'PERFORMING ARTS':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'POP CULTURE':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;

		case 'PUBLIC':
		$series_program_type_formatted = "Public Affairs";
		break;
		case 'PUBLIC AFFAIRS':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'SCIENCE':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		case 'TV-G':
		$series_program_type_formatted = $series_program_type;
		break;
		
		case 'WOMENS':
		$series_program_type_formatted = ucwords(strtolower($series_program_type));
		break;
		
		default:
		$series_program_type_formatted = "";
		break;
	}
	return $series_program_type_formatted;
}

/**
 * Fix the taxonomy for Episode Stereo type
 */
function episode_import_stereo_fix($episode_stereo) {
	switch ($episode_stereo) {

		case 'STEREO':
		$episode_stereo_formatted = ucwords(strtolower($episode_stereo));
		break;
		
		case 'MONO':
		$episode_stereo_formatted = ucwords(strtolower($episode_stereo));
		break;
		
		case 'SRND51':
		$episode_stereo_formatted = 'Stereo Surround 5.1';
		break;

		default:
		$episode_stereo_formatted = "";
		break;
	}
	return $episode_stereo_formatted;
}

/**
 * Fix the taxonomy for Episode Letterbox type
 */
function episode_import_letterbox_fix($episode_letterbox) {
	switch ($episode_letterbox) {

		case 'Widescreen':
		$episode_letterbox_formatted = ucwords(strtolower($episode_letterbox));
		break;
		
		case 'Letterbox':
		$episode_letterbox_formatted = ucwords(strtolower($episode_letterbox));
		break;
		
		case 'P':
		$episode_letterbox_formatted = 'Pillarbox';
		break;

		case 'N':
		$episode_letterbox_formatted = '';
		break;

		case 'U':
		$episode_letterbox_formatted = '';
		break;

		default:
		$episode_letterbox_formatted = "";
		break;
	}
	return $episode_letterbox_formatted;
}

/**
 * This is a standardized upcoming airdate display.
 * It's very picky.
 */
function format_upcoming_dates($vars) {
  // Initially ensure that there's a value present
  if(!empty($vars)) {
    // Get the dates to work with
    $date = $vars['element']['#items'][0]['kued_feature'];
    $channel = $vars['element']['#items'][0]['kued_feature_station'];
    $now = REQUEST_TIME;
     
    // Get some test dates (day number in the year)
    $test_date = date('z', $date);
    $test_now = date('z', $now);
    $fulldate = date('Y-m-d H:i:s', $date);
  
    // Check to see if this year is already in the DB
    $query = db_select('protrack_airlist', 'p')
      ->fields('p')
      ->condition('fulldate', date('Y-m-d H:i:s', $date), '=')
      ->condition('channel', $channel, '=')
      ->range(0,10);
    $result = $query->execute();
    $record = $result->fetchAssoc();
    $channel = channel_fix($record['channel']);
  
    // Check to see if the date has alread passed
    // if so do nothing.
    if($date > $now) {
      // Date is in the future, now tell everyone when it airs.
      // personalize the date a little bit
      if($test_date == $test_now) {
        if(date('G', $date) > 17) {
          $response = '<div class="' . $vars['field_name_css'] . '-today evening">Tonight at <span class="' . $vars['field_name_css'] . '-date">' . date('g:i A', $date) . '</span> on ' . $channel . '</div>';
        } else {
          $response = '<div class="' . $vars['field_name_css'] . '-today day">Today at <span class="' . $vars['field_name_css'] . '-date">' . date('g:i A', $date) . '</span> on ' . $channel . '</div>';
        }
      } elseif($test_date - $test_now == 1) {
        if(date('G', $date) > 17) {
          $response = '<div class="' . $vars['field_name_css'] . '-tomorrow evening">Tomorrow night at <span class="' . $vars['field_name_css'] . '-date">' . date('g:i A', $date) . '</span> on ' . $channel . '</div>';
        } else {
          $response = '<div class="' . $vars['field_name_css'] . '-tomorrow day">Tomorrow at <span class="' . $vars['field_name_css'] . '-date">' . date('g:i A', $date) . '</span> on ' . $channel . '</div>';
        }
      } else {
        if(date('W', $date) == date('W', $now)) {
          if(date('G', $date) > 17) {
            $response = '<div class="' . $vars['field_name_css'] . '-this-week evening">' . date('l', $date) . ' evening at <span class="' . $vars['field_name_css'] . '-date">' . date('g:i A', $date) . '</span> on ' . $channel . '</div>';
          } else {
            $response = '<div class="' . $vars['field_name_css'] . '-this-week day">This ' . date('l', $date) . ' at <span class="' . $vars['field_name_css'] . '-date">' . date('g:i A', $date) . '</span> on ' . $channel . '</div>';
          }
        } else {
          $response = '<div class="' . $vars['field_name_css'] . '-upcoming">' . date('l, M j, g:i A', $date) . ' on ' . $channel . '</div>';
        }
      }
    } else {
      //do nothing...
      $response = '';
    }
    $response = '<div class="' . $vars['classes'] . '"><div class="field-items"><div class="field-item">' . $response . "</div></div></div>";
  }
  return $response;
}

/**
 * Fix the taxonomy for Channel
 */
function channel_fix($channel) {
	switch ($channel) {

		case 'KUED-HD':
		case 'KUED':
		$channel_formatted = 'KUED';
		break;

		case 'World':
		case 'WORLD':
		$channel_formatted = 'The World';
		break;

    case 'kids ch':
    case 'Kids Ch':
    case 'KIDS CH':
    case 'kids':
    case 'kids24-7':
		$channel_formatted = 'Kids 24/7';
		break;

    case 'Create':
    case 'CREATE':
    case 'create':
		$channel_formatted = 'Create';
		break;

		default:
		$channel_formatted = '';
		break;

	}
	return $channel_formatted;
}

/**
 * Converts program length into seconds
 */
function length_to_seconds($time) {
    $hours = substr($time, 0, -6);
    $minutes = substr($time, -5, 2);
    $seconds = substr($time, -2);
    return $hours * 3600 + $minutes * 60 + $seconds;
}

/**
 * Imports caption files from PBS video
 */
function caption_cove_prepare($video) {
	// include the API function
	if(module_load_include('inc', 'kued_data', 'kued_data.functions')) {

		// Look for caption files
		if($video['captions'][1]['url']) {
			$file_url = $video['captions'][1]['url'];
		} elseif ($video['captions'][0]['url']) {
			$file_url = $video['captions'][0]['url'];
		}  elseif ($video['captions'][2]['url']) {
			$file_url = $video['captions'][2]['url'];
		}  elseif ($video['captions'][3]['url']) {
			$file_url = $video['captions'][3]['url'];
		} else {
			drupal_set_message(t('Sorry, no caption file is available!'));
			return;
		}
		
		$file_url = str_replace(' ', '%20', $file_url);
		$directory = file_build_uri('media/captions');
		if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
			// If our directory doesn't exist and can't be created, use the default.
			$directory = NULL;
			drupal_set_message(t('Failed to create directory: media/captions'));
		}
		$file = system_retrieve_file($file_url, $directory, TRUE, FILE_EXISTS_REPLACE);
		if($file){
			//Set the file status to permanent so it is not deleted in next cron run
			$file->filename = $video['title'];
			$file->filemime = 'application/xml';
			$file->type = 'closed_caption';
			$file->field_url = $file_url;
			$file->status = FILE_STATUS_PERMANENT;
      
			file_save($file);

		} else {
		}
	}
	return($file->fid);
}

/**
 * Imports image files from PBS video
 */
function image_pbs_media_prepare($video) {
 	if(module_load_include('inc', 'kued_data', 'kued_data.functions')) {
    $video = $video['data']['attributes'];
		if($video['images'][0]['profile']) {
			$image_url = $video['images'][0]['image'];
			$directory = file_build_uri('media/video');
      if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
        // If our directory doesn't exist and can't be created, use the default.
        $directory = NULL;
        drupal_set_message('Failed to create directory: media/video');
      }

			$image = system_retrieve_file($image_url, $directory, TRUE, FILE_EXISTS_RENAME);
      if($image){
        //Set the file status to permanent so it is not deleted in next cron run
        $image->filename = $video['title'];
        $image->filemime = $image->filemime;
        $image->type = 'image';
        //$image->field_file_image_title_text = $video['description_long'];
        //$image->field_file_image_alt_text = $video['description_short'];
        $image->status = FILE_STATUS_PERMANENT;
        if(file_save($image)) {
          $fid = $image->fid;
          drupal_set_message('Image Successfully Imported, just ignore that message below.');
        }
      }
    }
  return $fid;
  }
}

/**
 * Imports video entities from PBS video
 */
function video_pbs_media_prepare($video) {
  $nid = '';
  $video = $video['data']['attributes'];

	if(module_load_include('inc', 'kued_data', 'kued_data.functions')) {
	  $language_formatted = 'und';
    
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'video')
      ->propertyCondition('title', $video['title'])
      ->range(0, 1);
    $result = $query->execute();
  
    if(empty($result)){

		//Begin the node import process
		$node = new stdClass(); // Create a new node object
		$node->type = 'video'; // video type
		node_object_prepare($node); // Set some default values
	
		//uid associated with this node
		$node->uid = 1; // UID of the author of the node; or use $node->name
		//Set the title
		$node->title = $video['title'];
		$node->language = $language_formatted;

		//Fix the description
		if(strlen($video['description_short'])) {
			$short_description = reverse_html(t('@description_short', array('@description_short' => $video['description_short'])));
		} else {
			$short_description = '';
		}
		if(strlen($video['description_long'])) {
			$long_description = reverse_html(t('@description_long', array('@description_long' => $video['description_long'])));
		} else {
			$long_description = '';
		}

		if($video['images'][0]['profile']) {
			$image_url = $video['images'][0]['image'];
			$directory = file_build_uri('media/video');
				if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
					// If our directory doesn't exist and can't be created, use the default.
					$directory = NULL;
					drupal_set_message('Failed to create directory: media/video');
				}

			$image = system_retrieve_file($image_url, $directory, TRUE, FILE_EXISTS_RENAME);
				if($image){
					file_usage_add($image, 'kued_data', 'node', $node->uid);

					$node->field_image['und'][0] = array(
						'fid' => $image->fid,
						'title' => $video['title'],
						'filesize' => $image->filesize,
						'filename' => $image->filename,
						'filemime' => $image->filemime,
						'description' => $short_description,
						'uri' => $image->uri,
						'uid' => $node->uid,
						'status' => 1,
						'display' => 1,
					);

					//Set the file status to permanent so it is not deleted in next cron run
					$image->filename = $video['title'];
					$image->filemime = $image->filemime;
					$image->type = 'image';
					$image->status = FILE_STATUS_PERMANENT;
					file_save($image);
				}
			}

		//Insert Summary
		if(strlen($short_description)) {
			$node->body[$node->language][0]['summary'] = $short_description;
		}
		//Insert Description
		if(strlen($long_description)) {
			$node->body[$node->language][0]['value'] = $long_description;
		}
		$node->body[$node->language][0]['format'] = 'full_html';
		$node->field_notes[$node->language][0]['format'] = 'full_html';

		//Insert Rating Term
    if($video['content_rating'] != '') {
      $video['content_rating'] = strtoupper(str_replace('-', '', $video['content_rating'])); // Remove the hyphen to play well with my taxonomy
      if($rating_tid = taxonomy_get_term_by_name($video['content_rating'])) {
        $rating_keys = array_keys($rating_tid);
        $node->field_episode_rating[$node->language][0]['tid'] = $rating_keys[0];
      }
    }

    //Insert Category Term
    switch ($video['object_type']) {
      case 'full_length':
        $category_name = 'Full Length';
      break;
      case 'clip':
        $category_name = 'Clip';
      break;
      case 'preview':
        $category_name = 'Preview';
      break;
    }
    if($category_tid = taxonomy_get_term_by_name($category_name)) {
      $category_keys = array_keys($category_tid);
      $node->field_video_category[$node->language][0]['tid'] = $category_keys[0];
    }

		//Insert COVE Embed Code
		if(strlen($video['player_code'])) {
      // Extract the COVE ID Hash value from the Partner Player
      // Examples:
      //MMBM5bIn8k1xxkWWIeL4DQ==
      //MMBM5bIn8k1xxkWWIeL4DQ%3D%3D
      $match_pattern = '/%3D%3D/';
      $replacement = '==';
      // Check to see if the embed code has been URL Encoded
      if(preg_match($match_pattern, $video['player_code'])) {
        $pattern = '%3D%3D';
        $replacement = '==';
        $video['player_code'] = str_replace($pattern, $replacement, $video['player_code']);
      }
      // Now extract the hash tag for embedding
      $cove_video_id_hash = explode('==', $video['player_code']);
      $cove_video_id_hash = substr($cove_video_id_hash[0], -22) . '==';
			$node->field_cove_video_id_hash[$node->language][0]['value'] = $cove_video_id_hash;
		}

		//Insert COVE Video ID
		if(strlen($video['legacy_tp_media_id'])) {
			$node->field_cove_video_id[$node->language][0]['value'] = $video['legacy_tp_media_id'];
		}

		//Insert embed flag
		if($video['can_embed_player'] == TRUE) {
			$node->field_cove_embed[$node->language][0]['value'] = 1;
		} else {
			$node->field_cove_embed[$node->language][0]['value'] = 0;
		}

		//Insert original Airdate
		if(strlen($video['premiered_on']) && $video['premiered_on'] != 'None') {
			$node->field_original_airdate[$node->language][0] = array(
				'value' => date('Y-m-d H:i:s', strtotime($video['premiered_on'])),
				'timezone' => 'UTC',
			);
		}

		// Insert Update Time
		$node->created = REQUEST_TIME;
		if($video['updated_at'] != 'None' && $video['updated_at'] != '') {
			$video_update = strtotime($video['updated_at']);
			// if the update is in the past that could be trouble, check it
			if($video_update > REQUEST_TIME) {
				$node->changed = $video_update;
			} else {
				$node->changed = REQUEST_TIME;
			}
		} else {
			$node->changed = REQUEST_TIME;	
		}
		// Generic Status settings
		$node->status = 1;
		$node->promote = 0;
		$node->revision = 0;

		//Save the new node!
		if($node = node_submit($node)) {
			node_save($node);
			$nid = $node->nid;
		}

		// Now that the Node is created we can handle the unschedule portion
		if($video['availabilities']['public']['start'] != 'None' && $video['availabilities']['public']['start'] != ''){
			$video_available = strtotime($video['availabilities']['public']['start']);
			if($video_available > REQUEST_TIME) {
        $publish = array(
          'nid' => $nid,
          'publish_on' => $video_available,
          );
        db_insert('scheduler')
          ->fields($publish)
          ->execute();
			}
		}

		// Now that the Node is created we can handle the unschedule portion
		if($video['availabilities']['public']['end'] != 'None' && $video['availabilities']['public']['end'] != ''){
			$video_expire = strtotime($video['availabilities']['public']['end']);
        $expire = array(
          'nid' => $nid,
          'unpublish_on' => $video_expire,
          );
        db_insert('scheduler')
          ->fields($expire)
          ->execute();
      }
    }
  	if(!empty($nid)){
			return $nid;
		}
	} else {
		return array();
	}
}
