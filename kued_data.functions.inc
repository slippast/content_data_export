<?php
/**
 * These functions clean up the messy kued_data text
 */

// Function to clean the MS text that finds its way in here...
function kued_data_fix_text($fixed_string) {
	$ms_bad_characters = array(chr(145), chr(146), chr(147), chr(148), chr(150), chr(151), chr(133)); // Bad boy
	$ms_good_characters = array("'", "'", '"', '"', '-', '--', '...'); // Much Better
	$fixed_string = str_replace($ms_bad_characters, $ms_good_characters, $fixed_string); // Replace the nasty stuff now
	// Send the fix back
	return $fixed_string;
	}

// Function to clean the nasty kued_data tags from the titles
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

// Reverse HTML characters for insert
function reverse_html($reverse) {
	$translation = get_html_translation_table(HTML_SPECIALCHARS, ENT_QUOTES);
	$translation = array_flip($translation);
	$fixed_string = strtr($reverse, $translation);

	// Not sure why I have to do this but it's not getting the single quotes any other way
	$second_fix = array("&#039;" => "'");
	$fixed_string = strtr($fixed_string, $second_fix);

	return $fixed_string;
}

// Function to clean the nasty kued_data tags from the copyright
function kued_data_fix_copyright($fixed_string) {
	$bad_characters = array('Â'); // Bad boy
	$fixed_string = str_replace($bad_characters, '', $fixed_string); // Replace the nasty stuff now
	$fixed_string = trim($fixed_string);
	return $fixed_string;
}


/**
 * Now we use a couple of functions to format the Taxonomy Data because the stuff coming from ProTrack is ugly
 */

// Fix the taxonomy for Series entries
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


// Fix the taxonomy for Episode Stereo type
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

// Fix the taxonomy for Episode Letterbox type
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


// This is a standardized upcoming airdate display.
// It's very picky.
function format_upcoming_dates($vars) {
 // Initially ensure that there's a value present
 if(!empty($vars)) {
  // Get the dates to work with
  $date = $vars['element']['#items'][0]['kued_feature'];
  $now = REQUEST_TIME;
   
  // Get some test dates (day number in the year)
  $test_date = date('z', $date);
  $test_now = date('z', $now);

	// Check to see if this year is already in the DB
	$query = db_select('protrack_airlist', 'p')
		->fields('p')
		->condition('fulldate', date('Y-m-d H:i:s', $date), '=')
		->range(0,1);
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

// Fix the taxonomy for Channel
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



 
/*
 * This class implements the PBS COVE API v1 authentication protocol
 * The usage is straightforward:
 *
 *    $api_id = <Your COVE API ID>
 *    $api_secret = <Your COVE API Secret>
 *   
 *    $requestor = new COVE_API_Request($api_id,$api_secret);
 *    $json = $requestor->make_request("http://api.pbs.org/cove/v1/programs/?filter_producer__name=PBS");
 *
 * There are also alternative functions for generating the normalized url and
 * creating signatures if you wish to handle the API call yourself
 *
 */
class COVE_API_Request
{
    var $m_api_id = 'KUED-ba759e97-4109-49ed-974b-3741d6cddcf2';
    var $m_api_secret = '1988a78a-b478-4853-a4f1-4bba9cac4096';
 
    // Class can be constructed with our without passing in keys
    function __construct($api_id = '', $api_secret='')
    {
        if ($api_id <> '' && $api_secret <> '')
        {
            $this->set_auth_info($api_id,$api_secret);
        }
    }
     
    // This function can be used to change the credentials without
    // creating a new object
    function set_auth_info($api_id, $api_secret)
    {
        $this->m_api_id = $api_id;
        $this->m_api_secret = $api_secret;
    }
 
    // Establishes a normalized url:
    //   * Key/Value parameters are sorted
    //   * Values are url encoded and utf-8 encoded
    //
    function normalize_url($url)
    {
        if ($url == '')
            return '';
         
        // Break up the url into all the various components
        // we expect this to be a full url
        $parts = parse_url($url);
         
        // Extract just the query parameters
        $query = $parts['query'];
        if ($query)
        {
            // break out the parameters from the query, but only as a single
            // array of strings
            $params = explode('&', $query);
            // now we loop through each string and generate a tuple for a multi-array
            $parameters = array();
            foreach ($params as $p)
            {
                // Split this string into two parts and add to the multi-array
                list($key,$value) = explode('=',$p);
                // do the url encoding while we are looping here
                $parameters[$key] = utf8_encode(urlencode($value));
                //$parameters[$key] = $value;
            }
     
            // now sort the parameter list
            ksort($parameters);
             
            // Now combine all the parameters into a single query string
            $newquerystring = http_build_query($parameters);
            $newquerystring = '';
            foreach ($parameters as $key => $value)
            {
                $newquerystring = $newquerystring.$key.'='.$value.'&';
            }
            $newquerystring = substr($newquerystring,0,strlen($newquerystring)-1);           
            // combine everything into the total url
            $parts['query'] = "?".$newquerystring;
        }
        $party['scheme'] = 'http';
        $final_url = $parts['scheme'].'://'.$parts['host'].$parts['path'].$parts['query'];
        return ($final_url);
    }
     
    // Using the parameters, generate the hash for the combination
    // of the HTTP verb, the normalized url, the timestamp, nonce, and key
    //
    function calc_signature ($url, $timestamp, $nonce)
    {
        // Take the url and process it
        $normalized_url = $this->normalize_url($url);
         
        // Now combine all the required parameters into a single string
        // Note: We are always assuming 'get'
        $string_to_sign = "GET".$normalized_url.$timestamp.$this->m_api_id.$nonce;
 
        // And generate the hash using the secret
        $signature = hash_hmac('sha1',$string_to_sign, $this->m_api_secret);
         
        return($signature);
    }
 
    // If only the url is passed in, the timestamp and nonce
    // will be automatically generated
    //
    // Some proxies/firewalls and/or PHP configurations have problems using the
    // headers as the authentication mechanism so the default will be to use
    // the authentication parameters included in the url string.
    // If you are caching the API calls, it may be more advantageous to
    // utilize the header version.
    //
    // Returns the JSON response
    //
    //
    function make_request($url, $auth_using_headers=false, $timestamp=0, $nonce='')
    {
       // check to see if we need to autogenerate the parameters
        if ($timestamp == 0)
            $timestamp = time();
        if ($nonce == '')
            $nonce = md5(rand());
 
        if ($auth_using_headers == false)
        {
            // Pick the correct separator to use
            $separator = "?";
            if (strpos($url,"?")!==false)
                $separator = "&";
 
            $url = $url.$separator."consumer_key=".$this->m_api_id."&timestamp=".$timestamp."&nonce=".$nonce;
            $signature = $this->calc_signature($url, $timestamp, $nonce);
            // Now add signature at the end
            $url = $this->normalize_url($url."&signature=".$signature);
			//drupal_set_message('<pre><h2>Request URL:</h2>' . print_r($url) . '</pre><hr />');
			return(drupal_http_request($url));
            //return(file_get_contents($url));
 
        }
        else
        {
            $signature = $this->calc_signature($url, $timestamp, $nonce);
            // Put the authentication parameters into the HTTP headers
            // instead of into the url parameters
/*
            $options = array(
                'http'=>array(
                    'method'=>"GET",
                    'header'=>"X-PBSAuth-Timestamp: $timestamp\r\n" .
                              "X-PBSAuth-Consumer-Key: $this->m_api_id\r\n".
                              "X-PBSAuth-Signature: $signature\r\n".
                              "X-PBSAuth-Nonce: $nonce\r\n"
                    )
                );
*/
			$url = $this->normalize_url($url);
			$options = array(
				'method'=>"GET",
				'headers'=>"X-PBSAuth-Timestamp: $timestamp\r\n" .
				"X-PBSAuth-Consumer-Key: $this->m_api_id\r\n".
				"X-PBSAuth-Signature: $signature\r\n".
				"X-PBSAuth-Nonce: $nonce\r\n"
				//'data'=>"$url"
				);
			return(drupal_http_request($url, $options));
            //$context = stream_context_create($options);
            //return(file_get_contents($url, FALSE, $context));      
        }
 
    }
}


////////////////////
function caption_cove_prepare($video) {
	// include the API function
	if(module_load_include('inc', 'kued_data', 'kued_data.functions')){

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
		//drupal_set_message('<pre><h2>file_url:</h2>' . print_r($file_url, TRUE) . '</pre>');
		$directory = file_build_uri('media/captions');
		//drupal_set_message('<pre><h2>directory:</h2>' . print_r($directory, TRUE) . '</pre>');
		if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
			// If our directory doesn't exist and can't be created, use the default.
			$directory = NULL;
			drupal_set_message(t('Failed to create directory: media/captions'));
		}
		$file = system_retrieve_file($file_url, $directory, TRUE, FILE_EXISTS_REPLACE);
	//drupal_set_message('<pre><h2>file1:</h2>' . print_r($file, TRUE) . '</pre>');
		if($file){
			//Set the file status to permanent so it is not deleted in next cron run
			$file->filename = $video['title'];
			$file->filemime = 'application/xml';
			$file->type = 'closed_caption';
			$file->field_url = $file_url;
			$file->status = FILE_STATUS_PERMANENT;
			//drupal_set_message('<pre><h2>file2:</h2>' . print_r($file, TRUE) . '</pre>');
			file_save($file);
			//dpm('file saved');

			/*
			$file = (array)$file;
			$items = array($file);
			dpm('create entity type: file');
			$entity_type = 'file';
			$cc_entity = entity_create($entity_type, array('type' => 'closed_caption'));
			dpm('create entity');
			dpm($cc_entity);
			$cc_entity_wrapper = entity_metadata_wrapper($entity_type, $cc_entity);
			dpm('create wrapper');
			dpm($cc_entity_wrapper);
			$cc_entity_wrapper->field_filename->set($video['title']);
			dpm('set document');
			$cc_entity_wrapper->save();
			dpm('save');
			*/
		} else {
			// handle images some other way?
		}
	}
	return($file->fid);
}



////////////////////
function video_cove_prepare($video) {
	//dpm('video_cove_prepare called');
	// include the API function
	if(module_load_include('inc', 'kued_data', 'kued_data.functions')){

	$language_formatted = 'und'; // Let's just make everything undetermined, sadly.

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
	  ->entityCondition('bundle', 'video')
	  ->propertyCondition('title', $video['title'])
	  ->range(0, 1);
	$result = $query->execute();
	
	//drupal_set_message('<pre><h2>field query:</h2>' . print_r($result, TRUE) . '</pre>');

	if(empty($result)){
		//drupal_set_message('<pre><h2>Video:</h2>' . print_r($video, TRUE) . '</pre>');
		//drupal_set_message('<pre>Video: <strong>' . $video['title'] . '</strong></pre><br />');

		//Begin the node import process
		$node = new stdClass(); // Create a new node object
		$node->type = "video"; // video type
		node_object_prepare($node); // Set some default values
	
		//uid associated with this node
		$node->uid = 1; // UID of the author of the node; or use $node->name
		//Set the title
		$node->title = $video['title'];
		//$node->language = $language_formatted;
		$node->language = $language_formatted;

		//Now insert the series reference
		if(!empty($video['series_reference'])) {
			$node->field_series_link[$node->language][0]['target_id'] = $video['series_reference'];
		}
		//Now insert the episode reference
		if(!empty($video['episode_reference'])) {
			$node->field_episode_cross_link[$node->language][0]['target_id'] = $video['episode_reference'];
		}

		//Fix the guide
		if(strlen($video['short_description'])) {
			$short_description = reverse_html(t('@short_description', array('@short_description' => $video['short_description'])));
			//$episode_guide = reverse_html($episode_guide);
		} else {
			$short_description = '';
		}
	
		//Fix the description
		if(strlen($video['long_description'])) {
			$long_description = reverse_html(t('@long_description', array('@long_description' => $video['long_description'])));
			//$episode_description = reverse_html($episode_description);
		} else {
			$long_description = '';
		}

/*
		//If there is no guide use the episode_description
		if(empty($short_description)) {
			$episode_guide = truncate_utf8($episode_description, 40, $wordsafe = TRUE, $add_ellipsis = TRUE, $min_wordsafe_length = 30);
			$episode_guide = $episode_description;
		}
		//If there is no description use the episode_guide
		if(empty($episode_description)) {
			$episode_description = $short_description;
		}
*/


//////////////////////////////
////////////////////////
///////////////
///////////////////
//////////////////

		if($video['associated_images'][0]['type']['usage_type']['Mezzanine']) {
			$image_url = $video['associated_images'][0]['url'];
			//drupal_set_message('<pre><h2>image_url:</h2>' . print_r($image_url, TRUE) . '</pre>');
			$directory = file_build_uri('media/video');
			//drupal_set_message('<pre><h2>directory:</h2>' . print_r($directory, TRUE) . '</pre>');
				if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
					// If our directory doesn't exist and can't be created, use the default.
					$directory = NULL;
					drupal_set_message('Failed to create directory: media/video');
				}

			//$image = file_get_contents($image_url);
			//$image = file_save_data($image, $directory, FILE_EXISTS_REPLACE);

			$image = system_retrieve_file($image_url, $directory, TRUE, FILE_EXISTS_RENAME);
			//drupal_set_message('<pre><h2>image:</h2>' . print_r($image, TRUE) . '</pre>');
				if($image){
					file_usage_add($image, 'kued_data', 'node', $node->uid);
					//$node->field_image[$node->language][0] = $image;

					$node->field_image['und'][0] = array(
						'fid' => $image->fid,
						'title' => $video['title'],
						//'filepath' => $image,
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
					//drupal_set_message('<pre><h2>image:</h2>' . print_r($image, TRUE) . '</pre>');
					file_save($image);

				//$node->field_image['und'][0]['field_episode_header_image_fid'] = $image-fid;
				//$node->field_image['und'][0]['entity_id'] = $node->nid;
				//$node->field_image['und'][0]['field_episode_header_image_fid'] = $image-fid;
				//$node->field_image['und'][0]['field_episode_header_image_fid'] = $image-fid;
				}
			} else {
				// handle images some other way?
			}


		//Insert Summary
		if(strlen($short_description)) {
			//$node->field_description[$node->language][0]['value'] = $short_description;
			//$node->body->summary->set(array('value' => $short_description));
			$node->body[$node->language][0]['summary'] = $short_description;
		}
		//Insert Description
		if(strlen($long_description)) {
			//$node->body[$node->language][0]['value'] = $long_description;
			$node->body[$node->language][0]['value'] = $long_description;
			//$node->body->set(array('value' => $long_description));
		}

		$node->body[$node->language][0]['format'] = 'full_html';
		$node->field_notes[$node->language][0]['format'] = 'full_html';

		//Insert Rating Term
		$video['rating'] = strtoupper(str_replace('-', '', $video['rating'])); // Remove the hyphen to play well with my taxonomy
		if($rating_tid = taxonomy_get_term_by_name($video['rating'])) {
			$rating_keys = array_keys($rating_tid);
			$node->field_episode_rating[$node->language][0]['tid'] = $rating_keys[0];
		}

		//Insert Category Term
		//$video['type'] = strtoupper(str_replace('-', '', $video['type'])); // Remove the hyphen to play well with my taxonomy
		if($category_tid = taxonomy_get_term_by_name($video['type'])) {
			$category_keys = array_keys($category_tid);
			$node->field_video_category[$node->language][0]['tid'] = $category_keys[0];
		}

		//Insert COVE Embed Code
		if(strlen($video['partner_player'])) {
      // Extract the COVE ID Hash value from the Partner Player
      // Examples:
      //MMBM5bIn8k1xxkWWIeL4DQ==
      //MMBM5bIn8k1xxkWWIeL4DQ%3D%3D
      $match_pattern = '/%3D%3D/';
      $replacement = '==';
      // Check to see if the embed code has been URL Encoded
      if(preg_match($match_pattern, $video['partner_player'])) {
        $pattern = '%3D%3D';
        $replacement = '==';
        $video['partner_player'] = str_replace($pattern, $replacement, $video['partner_player']);
      }
      // Now extract the hash tag for embedding
      $cove_video_id_hash = explode('==', $video['partner_player']);
      $cove_video_id_hash = substr($cove_video_id_hash[0], -22) . '==';
			$node->field_cove_video_id_hash[$node->language][0]['value'] = $cove_video_id_hash;
		} else {
		}
		//Insert COVE Video ID
		if(strlen($video['tp_media_object_id'])) {
			$node->field_cove_video_id[$node->language][0]['value'] = $video['tp_media_object_id'];
		}
		//Insert embed flag
		if($video['allow_embed'] == 1) {
			$node->field_cove_embed[$node->language][0]['value'] = 1;
		} else {
			//$node->field_cove_embed[$node->language][0]['value'] = 0;
			$node->field_cove_embed[$node->language][0]['value'] = 1;
		}
		// Insert Episode page link
		if($video['episode_url']) {
			$node->field_sponsor_url[$node->language][0]['url'] = $video['episode_url'];
			$node->field_sponsor_url[$node->language][0]['title'] = $video['title'];
		}
		//Insert Copyright
		if(strlen($video['copyright'])) {
			$video['copyright'] = t(kued_data_fix_copyright($video['copyright']));
			$node->field_copyright[$node->language][0]['value'] = $video['copyright'];
		}
		//Insert Transcript Link
		if(strlen($video['transcript_url'])) {
			$node->field_url[$node->language][0]['value'] = $video['transcript_url'];
		}
		//Insert original Airdate
		if(strlen($video['airdate']) && $video['airdate'] != 'None') {
			//$node->field_original_airdate[$node->language][0]['value'] = intval(strtotime($video['airdate']));
			$node->field_original_airdate[$node->language][0] = array(
				'value' => date('Y-m-d H:i:s', strtotime($video['airdate'])),
				'timezone' => 'UTC',
				//'timezone_db' => 'UTC',
			);
		}

		// Insert Update Time
		$node->created = REQUEST_TIME;
		if($video['record_last_updated_datetime'] != 'None' && $video['record_last_updated_datetime'] != '') {
			$video_update = $video['record_last_updated_datetime'];
			$video_update = strtotime($video_update);
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
		//drupal_set_message(t('made it'));
			node_save($node);
			$nid = $node->nid;
		}

		// Now that the Node is created we can handle the unschedule portion
		if($video['available_datetime'] != 'None' && $video['available_datetime'] != ''  && is_numeric($video['available_datetime']) == TRUE){
			$video_available = strtotime($video['available_datetime']);
			if($video_available > REQUEST_TIME) {
			//$video_available = $video_available;
			//drupal_set_message('<pre>video_available1: '.print_r($video['available_datetime'], TRUE).'</pre>');
			//drupal_set_message('<pre>video_available2: '.print_r($video_available, TRUE).'</pre>');
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
		if($video['expire_datetime'] != 'None' && $video['expire_datetime'] != ''){
			$video_expire = strtotime($video['expire_datetime']);
			//$video_expire = $video_expire;
			//drupal_set_message('<pre>video_expire1: '.print_r($video['expire_datetime'], TRUE).'</pre>');
			//drupal_set_message('<pre>video_expire2: '.print_r($video_expire, TRUE).'</pre>');
			$expire = array(
				'nid' => $nid,
				'unpublish_on' => $video_expire,
				);
			db_insert('scheduler')
				->fields($expire)
				->execute();
		}
	} else {
		//drupal_set_message('<pre><h2>Update the node:</h2>' . print_r($result, TRUE) . '</pre><hr />');
		//$node = node_load(array('title' => 'node title', 'type' => 'page'));
	}
		if(!empty($nid)){
			return $nid;
		}
	} else {
		//drupal_set_message(t('Video already exists.'));
		return array();
	}
}

