<?php

/**
 * Private function to find all content types that have an entity references.
 */
function kued_data_connect_get_content_types() {
	$fields = field_info_fields();
	$content = array();
	foreach ($fields as $field_name => $field_data) {
		// Filter out stuff.
		if($field_data['module'] == 'entityreference' && $field_data['deleted'] != 1) {
			foreach($field_data['bundles'] as $bundle_type => $bundle){
				foreach($bundle as $content_type){
					$content[$bundle_type.",".$content_type.",".$field_data['field_name']] = $bundle_type.': '.$content_type." (".$field_data['field_name'].")";
				}
			}
		}
	}
  asort($content);
  return $content;
}

/**
 * Data connection
 */
function kued_data_connect_run($source, $target){
	$source_parts = explode(',', $source);
	$target_parts = explode(',', $target);

  $query = new EntityFieldQuery();
	$query->entityCondition('entity_type', $source_parts[0])
		->entityCondition('bundle', $source_parts[1])
		->count();
  $source_count = $query->execute();

  $query = new EntityFieldQuery();
	$query->entityCondition('entity_type', $target_parts[0])
		->entityCondition('bundle', $target_parts[1])
		->count();
  $target_count = $query->execute();

  $main_query = new EntityFieldQuery();
	$main_query->entityCondition('entity_type', $source_parts[0])
		->entityCondition('bundle', $source_parts[1])
		//->range(0, 2)
		->addMetaData('account', user_load(1)); // Run the query as user 1.
  $source_nodes = $main_query->execute();

  foreach($source_nodes['node'] as $source_node) {
		$node = node_load($source_node->nid, $source_node->vid, TRUE);

		$query = new EntityFieldQuery();
		$query->entityCondition('entity_type', $target_parts[0])
			->entityCondition('bundle', $target_parts[1])
			->propertyCondition('title', $node->title, '=');
			$result = $query->execute();
		if($result) {
			foreach($result as $node_info) {
				$nid = key($node_info);
				$node_update = node_load($nid);
				if(!isset($node->field_location_link[$node->language][0]['target_id']) && $node->field_location_link[$node->language][0]['target_id'] != $node_update->nid){
				$node->field_location_link[$node->language][0]['target_id'] = $node_update->nid;
					//Save the node!
					if($node = node_submit($node)) {
						node_save($node);
						$nid = $node->nid;
					}
				}	
			}
		} else {
      // Do nothing
		}
  }
}

/**
 * Batch process for connecting nodes
 */
function kued_data_connect_batch($node_count, $nodes) {
	$redirect_path = 'admin/config/content/kued/data/connect';
  // Give helpful information about how many nodes are being operated on.
  $batch = array(
		'title' => t('Connecting Nodes'),
    'operations' => array(
    	array('kued_data_connect_operation', $fuck),
    	array('kued_data_connect_operation_die'),
    ),
    //'finished' => 'kued_data_connect_operation_finished',
    'init_message' => t('Beginning process...'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Process had an error.'),
  );

  // set batch
  batch_set($batch);
  // process batch
  batch_process($redirect_path);
}

/**
 * Batch operation 
 */
/*
// Kept for reference
function _kued_data_connect_operation($operations, &$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    // Save node count for the termination message.
    $context['sandbox']['max'] = $operations['node_count'];
  }
  $limit = 5;
  $result = array('stuff','more','howdy');

  // Retrieve the next group of nids.
  $result = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->orderBy('n.nid', 'ASC')
    ->where('n.nid > :nid', array(':nid' => $context['sandbox']['current_node']))
    ->extend('PagerDefault')
    ->limit($limit)
    ->execute();

    foreach($operations['node'] as $source_node) {
      $node = node_load($source_node->nid, $source_node->vid, TRUE);
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', $target_parts[0])
        ->entityCondition('bundle', $target_parts[1])
        ->propertyCondition('title', $node->title, '=');
        $result = $query->execute();
      if($result){
        foreach($result as $node_info){
          //dsm($node_info);
          $nid = key($node_info);
          //dsm($nid);
          $node_update = node_load($nid);
          if(!isset($node->field_location_link[$node->language][0]['target_id']) && $node->field_location_link[$node->language][0]['target_id'] != $node_update->nid){
          $node->field_location_link[$node->language][0]['target_id'] = $node_update->nid;
  
            //Save the node!
            if($node = node_submit($node)) {
            //drupal_set_message(t('made it'));
              //node_save($node);
              //$nid = $node->nid;
            }
          }	
        }
        $node_update = node_load(array_keys($node_update), TRUE);
      } else {
		}
  }

  foreach ($result as $row) {
    // Here we actually perform our dummy 'processing' on the current node.
    //$node = node_load($row->nid, NULL, TRUE);
    // Store some results for post-processing in the 'finished' callback.
    // The contents of 'results' will be available as $results in the
    // 'finished' function (in this example, batch_example_finished()).
    //$context['results'][] = $node->nid . ' : ' . check_plain($node->title) . ' ' . $operation_details;
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $node->nid;
    $context['message'] = check_plain($row);
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
  //_batch_example_update_http_requests();

}
*/

/**
 * Batch 'finished' callback used by both batch 1 and batch 2.
 */
 /*
 // Kept for reference
function kued_data_connect_operation_finished($success, $results, $operations) {
	dsm('step 5');
  if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('Connections complete'));
    //drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occured, you can try running the operation again.'));
  }
}
*/
