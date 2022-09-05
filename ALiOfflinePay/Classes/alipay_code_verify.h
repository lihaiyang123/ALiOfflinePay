/****************************************************************************
 * IoTPay modules 1.0 2019/3/4
 * This software is provided "AS IS," without a warranty of any kind. ALL
 * EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING
 * ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. ALIPAY, INC.
 * AND ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE
 * AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
 * DERIVATIVES. IN NO EVENT WILL ALIPAY OR ITS LICENSORS BE LIABLE FOR ANY LOST
 * REVENUE, PROFIT OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL,
 * INCIDENTAL OR PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY
 * OF LIABILITY, ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE,
 * EVEN IF ALIPAY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 ****************************************************************************
 * You acknowledge that this software is not designed, licensed or intended
 * for use in the design, construction, operation or maintenance of any
 * nuclear facility.
*****************************************************************************/
#ifndef __ALIPAY_CODE_VERIFY_H__
#define __ALIPAY_CODE_VERIFY_H__

#ifdef __cplusplus
extern "C" { 
#endif

#include <stdint.h>
#include <time.h>



#define TIME_SIZE 8
#define DATA_FORMWORK_ID_LENGTH 4
#define PID_SIZE 8
#define SIZE_RESULT_STRING 32
#define PAYLOAD_LEN_MIN 512

/*
 * 用户权限枚举
 */
typedef enum
{
    ALIPAY_USER_PRORITY_IGNORE = 0,
    ALIPAY_USER_PRORITY_AGENT = 1,
    ALIPAY_USER_PRORITY_MAX,
}alipay_user_prority_e;

/*
 * 离线码版本号枚举
 */
typedef enum
{
    ALIPAY_CODE_VERSION_V1 = 1,
    ALIPAY_CODE_VERSION_V2 = 2,
} alipay_code_version_e;

/*
 * 返回值枚举
 */
typedef enum
{
    ALIPAY_CODEVERIFY_FAILED_UNREGISTERED = -5,//接口未注册
    ALIPAY_CODEVERIFY_FAILED_ILLEGAL_CODE = -4,//码不合法，
    ALIPAY_CODEVERIFY_FAILED_WRONG_RESULT_PARAMS = -3,//输入的参数result或者len_result不合法
    ALIPAY_CODEVERIFY_FAILED_WRONG_PARAMS = -2,//输入的其它参数不合法
    ALIPAY_CODEVERIFY_FAILED_NORMAL = -1,//码解析校验失败
    ALIPAY_CODEVERIFY_OK = 0,//验码成功
}alipay_codeverify_result_e;


typedef struct _os_adapter_layer_handler
{
    void (*alipay_get_sys_time)(uint64_t *time_now);//获取系统时间
} os_adapter_layer_handler;


/*
 * 注册适配层接口
 */
void alipay_adapter_register(os_adapter_layer_handler *handler);

/*
校验结果码（uint8_t型字符串）
----------------------------------------
结果                解释
----------------------------------------
DES_ERROR           码解密失败
INST_SIGN_FAILED	机构信息签名验证失败
USER_SIGN_FAILED	用户授权信息签名验证失败
RUN_EXCEPTION	    运行中程序遇到异常
USER_AUTH_TIMEOUT   授权证书过期
CODE_TIMROUT        二维码过期
SUCCESS	            成功
----------------------------------------
*/

/*
 * 双离线码验码接口
 */

/**
 * @oaram [in] code 码值
 * @param [in] len_code 码值长度
 * @param [in/out] result 作为入参要求不为空，作为出参表示校验结果码，参照前文注释
 * @param [in/out] len_result 作为入参要求输入result内存空间大小（不小于32），作为出参时表示result赋值后实际长度
 * @param [out] data_encode_type 用户数据编码格式
 * @param [in/out] payload 入参要求不为空，出参表示用户数据
 * @param [in/out] payload_len 入参要求输入payload内存空间大小（不小于512），出参表示实际用户数据长度
 * @param [in/out] data_formwork_id 入参要求不为空，出参表示用户数据模版码值 4bytes
 * @param [in/out] in_use_time 入参要求不为空，出参表示码生成时间，按照大端字节序，8bytes的字节流
 * 
 * 注意：所有参数的内存均为接口调用方申请，接口内部不申请相关内存
 * 
 * @return  ALIPAY_CODEVERIFY_FAILED_UNREGISTERED：接口未注册
 *          ALIPAY_CODEVERIFY_FAILED_ILLEGAL_CODE：输入的码不合法
 *          ALIPAY_CODEVERIFY_FAILED_WRONG_RESULT_PARAMS：输入的参数result或者len_result不合法
 *          ALIPAY_CODEVERIFY_FAILED_WRONG_PARAMS：输入的其他参数不合法
 *          ALIPAY_CODEVERIFY_FAILED_NORMAL：码解析校验失败
 *          ALIPAY_CODEVERIFY_OK：验码成功
 */
alipay_codeverify_result_e alipay_verify_code_info(const uint8_t *code,
    uint32_t code_len, uint8_t *result, uint32_t *result_len, uint32_t *data_encode_type,
    uint8_t data_formwork_id[DATA_FORMWORK_ID_LENGTH], uint8_t in_use_time[TIME_SIZE], uint8_t *payload, uint32_t *payload_len);


/**
 * sm2 sign
 *   d - private key
 *   id - id of sender, should be a byte array
 *   id_len - byte count of id
 *   msg - massege to be signed, should be a byte array
 *   msg_len - byte count of msg
 *   sig - (output) 64 bytes of signature
 * 
 * return value: 0 - succ, other - failed
 **/
int32_t sm2_sign(const uint8_t in_d[32],
             	 const uint8_t *id, uint32_t id_len,
                 const uint8_t *msg, uint32_t msg_len,
                 uint8_t sig[64]);


/**
 * sm2 verify
 *   pub - public key
 *   id - id of sender, should be a byte array
 *   id_len - byte count of id
 *   msg - massege to be signed, should be a byte array
 *   msg_len - byte count of msg
 *   sig - (output) 64 bytes of signature
 * 
 * return value: 0 - succ, other - failed
 **/

int32_t sm2_verify(const uint8_t pub[64],
             	  const uint8_t *id, uint32_t id_len,
                  const uint8_t *msg, uint32_t msg_len,
                  const uint8_t sig[64]);

int32_t sm2_verify2(const uint8_t pub[33],
             	  const uint8_t *id, uint32_t id_len,
                  const uint8_t *msg, uint32_t msg_len,
                  const uint8_t sig[64]);

/**
 * sm generate key pair
 *   out_d - private key
 *   out_px - public key x coordinate
 *   out_py - public key y coordinate
 * 
 * return value: 0 - succ, other - failed
 **/
int32_t sm2_gen_keypair(uint8_t out_d[32], uint8_t out_p[64]);
int32_t sm2_gen_keypair2(uint8_t out_d[32], uint8_t out_p[33]);

#ifdef __cplusplus 
} 
#endif 

#endif