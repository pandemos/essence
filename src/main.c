#include "directedbehaviour.h"
#include "qpc.h"
#include "signals.h"
#include "user.h"
#include "screen.h"
#include "input.h"
#include "vessel.h"
#include "physicaluniverse.h"
#include "temporaluniverse.h"
#include "staticbehaviour.h"
#include "priorityqueuebehaviour.h"
#include "prioritycurvebehaviour.h"
#include "bsp.h"

/*..........................................................................*/
int main() {
    static QSubscrList l_subscrSto[MAX_PUB_SIG];
    static QF_MPOOL_EL(QEvt) l_smlPoolSto[20]; /* small pool */

    static QEvt const *l_userQSto[10];
    static QEvt const *l_screenQSto[10];
    static QEvt const *l_vesselQSto[10];
    static QEvt const *l_physicaluniverseQSto[10];
    static QEvt const *l_temporaluniverseQSto[10];
    static QEvt const *l_staticbehaviourQSto[10];
    static QEvt const *l_directedbehaviourQSto[10];
    static QEvt const *l_priorityqueuebehaviourQSto[10];
    static QEvt const *l_prioritycurvebehaviourQSto[10];
    static QEvt const *l_inputQSto[10];

    QF_init();  /* initialize the framework and the underlying RT kernel */
    BSP_init(); /* initialize the Board Support Package */

    QF_psInit(l_subscrSto, Q_DIM(l_subscrSto));
    QF_poolInit(l_smlPoolSto, sizeof(l_smlPoolSto), sizeof(l_smlPoolSto[0]));

    /* instantiate and start the active objects... */

    User_ctor();
    QACTIVE_START(AO_User,
                  2U, /* This must be a unique QP priority ID */
                  l_userQSto,
                  Q_DIM(l_userQSto),
                  (void *)0,
                  0U,
                  (QEvt*)0);

	Screen_ctor();
	QACTIVE_START(AO_Screen,
				  3U, /* This must be a unique QP priority ID */
				  l_screenQSto,
				  Q_DIM(l_screenQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	Input_ctor();
	QACTIVE_START(AO_Input,
	              4U, /* This must be a unique QP priority ID */
	              l_inputQSto,
	              Q_DIM(l_inputQSto),
	              (void *)0,
	              0U,
	              (QEvt*)0);

	TemporalUniverse_ctor();
	QACTIVE_START(AO_TemporalUniverse,
				  5U, /* This must be a unique QP priority ID */
				  l_temporaluniverseQSto,
				  Q_DIM(l_temporaluniverseQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	PhysicalUniverse_ctor();
	QACTIVE_START(AO_PhysicalUniverse,
				  6U, /* This must be a unique QP priority ID */
				  l_physicaluniverseQSto,
				  Q_DIM(l_physicaluniverseQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	StaticBehaviour_ctor();
	QACTIVE_START(AO_StaticBehaviour,
				  7U, /* This must be a unique QP priority ID */
				  l_staticbehaviourQSto,
				  Q_DIM(l_staticbehaviourQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	DirectedBehaviour_ctor();
	QACTIVE_START(AO_DirectedBehaviour,
				  8U, /* This must be a unique QP priority ID */
				  l_directedbehaviourQSto,
				  Q_DIM(l_directedbehaviourQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	PriorityQueueBehaviour_ctor();
	QACTIVE_START(AO_PriorityQueueBehaviour,
				  9U, /* This must be a unique QP priority ID */
				  l_priorityqueuebehaviourQSto,
				  Q_DIM(l_priorityqueuebehaviourQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	PriorityCurveBehaviour_ctor();
	QACTIVE_START(AO_PriorityCurveBehaviour,
				  10U, /* This must be a unique QP priority ID */
				  l_prioritycurvebehaviourQSto,
				  Q_DIM(l_prioritycurvebehaviourQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

	Vessel_ctor();
	QACTIVE_START(AO_Vessel,
				  11U, /* This must be a unique QP priority ID */
				  l_vesselQSto,
				  Q_DIM(l_vesselQSto),
				  (void *)0,
				  0U,
				  (QEvt*)0);

    return QF_run(); /* run the QF application */
}
