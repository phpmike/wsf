

/**
* axis2_skel_ServiceGroupAdmin.c
*
* This file was auto-generated from WSDL for "ServiceGroupAdmin|http://mgt.service.carbon.wso2.org" service
* by the Apache Axis2/C version: #axisVersion# #today#
* axis2_skel_ServiceGroupAdmin Axis2/C skeleton for the axisService
*/

#include "codegen/axis2_skel_ServiceGroupAdmin.h"
#include "service_admin_constants.h"



/**
* auto generated function definition signature
* for "listServiceGroup|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _listServiceGroup of the adb_listServiceGroup_t*
*
* @return adb_listServiceGroupResponse_t*
*/
adb_listServiceGroupResponse_t* 
axis2_skel_ServiceGroupAdmin_listServiceGroup(const axutil_env_t *env , 
											  axis2_msg_ctx_t *msg_ctx,
											  adb_listServiceGroup_t* _listServiceGroup,
											  axis2_skel_ServiceGroupAdmin_listServiceGroup_fault *fault )
{
	axis2_char_t *svc_grp_name = NULL;
	adb_listServiceGroupResponse_t *response = NULL;
	axis2_conf_ctx_t *conf_ctx = NULL;
	axis2_svc_grp_ctx_t *svc_grp_ctx = NULL;
	axis2_svc_grp_t* svc_grp = NULL;
	axutil_hash_t *svc_map = NULL;
	axutil_array_list_t *adb_svc_list = NULL; /* contains a list of adb_ServiceMetaData_t */
	   axutil_array_list_t *adb_svc_types = NULL; /* contains list of service types(char*) */
    axutil_hash_t *service_types = NULL; /* to get the unique set of service types */
	 axis2_char_t *service_type_filter = NULL;
    axis2_char_t *svc_grp_filter = NULL;
	adb_ServiceGroupMetaData_t *svc_grp_metadata = NULL;
	axutil_hash_index_t *hi_svc = NULL;
	svc_grp_name = adb_listServiceGroup_get_serviceGroupName(_listServiceGroup, env);
	if(!svc_grp_name)
	{
		 AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Service Group name not given.");
        AXIS2_ERROR_SET(env->error,
			AXIS2_ERROR_SVC_SKEL_INVALID_OPERATION_PARAMETERS_IN_SOAP_REQUEST, AXIS2_FAILURE);
        return NULL;
	}
	conf_ctx = axis2_msg_ctx_get_conf_ctx(msg_ctx, env);
	svc_grp_ctx = axis2_conf_ctx_get_svc_grp_ctx(conf_ctx, env, svc_grp_name);
	if(svc_grp_ctx)
	{
		svc_grp = axis2_svc_grp_ctx_get_svc_grp(svc_grp_ctx, env);
	}
	if(!svc_grp)
	{
		AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Service Group not found for %s.", svc_grp_name);
		AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_OPERATION_PARAMETERS_IN_SOAP_REQUEST, AXIS2_FAILURE);
        return NULL;
	}

	response = adb_listServiceGroupResponse_create(env);

	svc_map = axis2_svc_grp_get_all_svcs(svc_grp, env);
	adb_svc_list = axutil_array_list_create(env, 0);
    for(hi_svc = axutil_hash_first(svc_map, env); hi_svc; hi_svc = axutil_hash_next(env, hi_svc))
    {
            axis2_svc_t *svc = NULL;
            axis2_char_t *svc_name = NULL;
            adb_ServiceMetaData_t *adb_svc = NULL;
            axis2_char_t *service_type = NULL;

            axutil_hash_this(hi_svc, &svc_name, NULL, &svc);
            /* Get the service type and filter using the given service type */
			{
			 axutil_param_t* param = NULL;

				 param = axis2_svc_get_param(svc, env, AXIS2_SERVICE_TYPE);
				if(!param)
				{
					/* Send default service type */
					service_type = AXIS2_DEFAULT_SERVICE_TYPE;
				}else{
					service_type = (axis2_char_t*)axutil_param_get_value(param, env);
				}
				if(axutil_strcmp(service_type_filter, DEFAULT_SERVICE_TYPE_FILTER) &&
					axutil_strcmp(service_type, service_type_filter))
				{
					/* filter is not satisfied */
					continue;
				}
			}
            /* check whether service type is already added, if not add it */
            if(!axutil_hash_get(service_types, service_type, AXIS2_HASH_KEY_STRING))
            {
                axutil_hash_set(service_types, service_type, AXIS2_HASH_KEY_STRING, service_type);
            }

            adb_svc = adb_ServiceMetaData_create(env);
            adb_ServiceMetaData_set_active(adb_svc, env, AXIS2_TRUE); /* TODO get this from somewhere */
            adb_ServiceMetaData_set_disableTryit(adb_svc, env, AXIS2_TRUE);
            /*adb_ServiceMetaData_set_tryitURL(adb_svc, env, "http://localhost:9090/test/tryit");*/
            adb_ServiceMetaData_set_name(adb_svc, env, svc_name);
            adb_ServiceMetaData_set_serviceType(adb_svc, env, service_type);

            /* TODO fix the wsdl endpoints */
            adb_ServiceMetaData_add_wsdlURLs(adb_svc, env, "http://localhost:9090/test?wsdl");
            adb_ServiceMetaData_add_wsdlURLs(adb_svc, env, "http://localhost:9090/test?wsdl2");

            axutil_array_list_add(adb_svc_list, env, adb_svc);
    }

    /* check whether there are atleast one service for this group. There might be empty groups
     * due to the filters
     */
    if(axutil_array_list_size(adb_svc_list, env))
    {
        svc_grp_metadata = adb_ServiceGroupMetaData_create(env);
        adb_ServiceGroupMetaData_set_serviceGroupName(svc_grp_metadata, env, svc_grp_name);
        adb_ServiceGroupMetaData_set_services(svc_grp_metadata, env, adb_svc_list);
        
    }
    else
    {
        axutil_array_list_free(adb_svc_list, env);
    }
	
	adb_ServiceGroupMetaData_set_services(svc_grp_metadata, env, adb_svc_list);
	{	
		axutil_param_t *param = axis2_svc_grp_get_param(svc_grp, env, AXIS2_ENABLE_MTOM);
		if(param)
		{
			adb_ServiceGroupMetaData_set_mtomStatus(svc_grp_metadata, env, axutil_param_get_value(param, env));
		}
	}

	adb_listServiceGroupResponse_set_return(response, env, svc_grp_metadata);

	return (adb_listServiceGroupResponse_t*)NULL;
}



/**
* auto generated function definition signature
* for "setServiceGroupParameters|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _setServiceGroupParameters of the adb_setServiceGroupParameters_t*
*
* @return 
*/
axis2_status_t  
axis2_skel_ServiceGroupAdmin_setServiceGroupParameters(const axutil_env_t *env , 
													   axis2_msg_ctx_t *msg_ctx,
													   adb_setServiceGroupParameters_t* _setServiceGroupParameters )
{
	/* TODO fill this with the necessary business logic */
	return AXIS2_SUCCESS;
}



/**
* auto generated function definition signature
* for "getServiceGroupParameter|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _getServiceGroupParameter of the adb_getServiceGroupParameter_t*
*
* @return adb_getServiceGroupParameterResponse_t*
*/
adb_getServiceGroupParameterResponse_t* 
axis2_skel_ServiceGroupAdmin_getServiceGroupParameter(const axutil_env_t *env , 
													  axis2_msg_ctx_t *msg_ctx,
													  adb_getServiceGroupParameter_t* _getServiceGroupParameter,
													  axis2_skel_ServiceGroupAdmin_getServiceGroupParameter_fault *fault )
{
	/* TODO fill this with the necessary business logic */
	return (adb_getServiceGroupParameterResponse_t*)NULL;
}



/**
* auto generated function definition signature
* for "configureServiceGroupMTOM|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _configureServiceGroupMTOM of the adb_configureServiceGroupMTOM_t*
*
* @return adb_configureServiceGroupMTOMResponse_t*
*/
adb_configureServiceGroupMTOMResponse_t* 
axis2_skel_ServiceGroupAdmin_configureServiceGroupMTOM(const axutil_env_t *env ,
													   axis2_msg_ctx_t *msg_ctx,
														adb_configureServiceGroupMTOM_t* _configureServiceGroupMTOM,
														axis2_skel_ServiceGroupAdmin_configureServiceGroupMTOM_fault *fault )
	{
	/* TODO fill this with the necessary business logic */
	return (adb_configureServiceGroupMTOMResponse_t*)NULL;
}



/**
* auto generated function definition signature
* for "removeServiceGroupParameter|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _removeServiceGroupParameter of the adb_removeServiceGroupParameter_t*
*
* @return 
*/
axis2_status_t  
axis2_skel_ServiceGroupAdmin_removeServiceGroupParameter(const axutil_env_t *env , 
														 axis2_msg_ctx_t *msg_ctx,
														  adb_removeServiceGroupParameter_t* _removeServiceGroupParameter )
{
	/* TODO fill this with the necessary business logic */
	return AXIS2_SUCCESS;
}



/**
* auto generated function definition signature
* for "updateServiceGroupParamters|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _updateServiceGroupParamters of the adb_updateServiceGroupParamters_t*
*
* @return 
*/
axis2_status_t  
axis2_skel_ServiceGroupAdmin_updateServiceGroupParamters(const axutil_env_t *env , 
														 axis2_msg_ctx_t *msg_ctx,
														 adb_updateServiceGroupParamters_t* _updateServiceGroupParamters,
														  axis2_skel_ServiceGroupAdmin_updateServiceGroupParamters_fault *fault )
{
	/* TODO fill this with the necessary business logic */
	return AXIS2_SUCCESS;
}



/**
* auto generated function definition signature
* for "dumpAAR|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _dumpAAR of the adb_dumpAAR_t*
*
* @return adb_dumpAARResponse_t*
*/
adb_dumpAARResponse_t* axis2_skel_ServiceGroupAdmin_dumpAAR(const axutil_env_t *env , axis2_msg_ctx_t *msg_ctx,
															adb_dumpAAR_t* _dumpAAR )
{
	/* TODO fill this with the necessary business logic */
	return (adb_dumpAARResponse_t*)NULL;
}



/**
* auto generated function definition signature
* for "setServiceGroupParameter|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _setServiceGroupParameter of the adb_setServiceGroupParameter_t*
*
* @return 
*/
axis2_status_t  axis2_skel_ServiceGroupAdmin_setServiceGroupParameter(const axutil_env_t *env , axis2_msg_ctx_t *msg_ctx,
																	  adb_setServiceGroupParameter_t* _setServiceGroupParameter )
{
	/* TODO fill this with the necessary business logic */
	return AXIS2_SUCCESS;
}



/**
* auto generated function definition signature
* for "updateServiceGroupParameter|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _updateServiceGroupParameter of the adb_updateServiceGroupParameter_t*
*
* @return 
*/
axis2_status_t  
axis2_skel_ServiceGroupAdmin_updateServiceGroupParameter(const axutil_env_t *env , 
														 axis2_msg_ctx_t *msg_ctx,
														 adb_updateServiceGroupParameter_t* _updateServiceGroupParameter,
														 axis2_skel_ServiceGroupAdmin_updateServiceGroupParameter_fault *fault )
{
	/* TODO fill this with the necessary business logic */
	return AXIS2_SUCCESS;
}



/**
* auto generated function definition signature
* for "listServiceGroups|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
*
* @return 
*/
axis2_status_t  
axis2_skel_ServiceGroupAdmin_listServiceGroups(const axutil_env_t *env , axis2_msg_ctx_t *msg_ctx )
{
	/* TODO fill this with the necessary business logic */
	return AXIS2_SUCCESS;
}



/**
* auto generated function definition signature
* for "getServiceGroupParameters|http://mgt.service.carbon.wso2.org" operation.
* @param env environment ( mandatory)* @param MessageContext the outmessage context
* @param _getServiceGroupParameters of the adb_getServiceGroupParameters_t*
*
* @return adb_getServiceGroupParametersResponse_t*
*/
adb_getServiceGroupParametersResponse_t* 
axis2_skel_ServiceGroupAdmin_getServiceGroupParameters(const axutil_env_t *env , 
													   axis2_msg_ctx_t *msg_ctx,
													   adb_getServiceGroupParameters_t* _getServiceGroupParameters,
													   axis2_skel_ServiceGroupAdmin_getServiceGroupParameters_fault *fault )
{
	/* TODO fill this with the necessary business logic */
	return (adb_getServiceGroupParametersResponse_t*)NULL;
}

