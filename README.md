# pic_timer

<br>
主な処理の説明
<br>

## pic_timer.h

<br>

データ構造体に、タイマーハンドル、led状態を追加

<pre>
typedef struct
{
    /* The application's current state */
    PIC_TIMER_STATES state;

    /* TODO: Define any additional data used by the application. */
    /*** add ***/
    SYS_TMR_HANDLE tmrHandle;                   // タイマーハンドル
    bool ledStatus;                             // led状態 false:OFF/true:ON
    /*** add ***/

} PIC_TIMER_DATA;
</pre>
<br>

## pic_timer.c

<br>

### 定期処理

定期処理の開始処理で、2秒間隔の周期タイマーを設定する。

<pre>
void PIC_TIMER_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( pic_timerData.state )
    {
        /* Application's initial state. */
        case PIC_TIMER_STATE_INIT:
        {
            bool appInitialized = true;
       
            /*** add ***/
            pic_timerData.ledStatus = false;
            
            // 2秒間隔の周期タイマー設定
            pic_timerData.tmrHandle = SYS_TMR_ObjectCreate( 2000, NULL, callbackTimer, SYS_TMR_FLAG_PERIODIC );
            /*** add ***/
            if (appInitialized)
            {
            
                pic_timerData.state = PIC_TIMER_STATE_SERVICE_TASKS;
            }
            break;
        }
        /*** 略 ***/
</pre>

<br>

### タイマーコールバック

<br>
2秒間隔でこの関数が呼ばれるので、呼ばれるたびにLEDをON→OFF→ON→ と切り替える。
<pre>
/*** add ***/
static void callbackTimer( uintptr_t context, uint32_t currTick ){
    // 2秒間隔で呼ばれる
    if(pic_timerData.ledStatus){
        // LED ON 状態
        LEDOff();
        pic_timerData.ledStatus = false;
    }
    else
    {
        // LED OFF 状態
        LEDOn();
        pic_timerData.ledStatus = true;
    }
    return;
}
/*** add ***/
</pre>
