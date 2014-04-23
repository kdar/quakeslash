#define NUM_EVENT_ARGS BOOST_PP_ITERATION()

#define NULLTYPE_MACRO(z, n, unused) detail::NullType

template<BOOST_PP_ENUM_PARAMS(NUM_EVENT_ARGS, typename T)>
class Event<BOOST_PP_ENUM_PARAMS(NUM_EVENT_ARGS, T)
BOOST_PP_COMMA_IF(BOOST_PP_AND(BOOST_PP_GREATER(NUM_EVENT_ARGS, 0), BOOST_PP_LESS(NUM_EVENT_ARGS, MAX_EVENT_ARGS)))
BOOST_PP_ENUM(BOOST_PP_SUB(MAX_EVENT_ARGS, NUM_EVENT_ARGS), NULLTYPE_MACRO, ~)> : public boost::noncopyable
{
private:
	typedef fastdelegate::BOOST_PP_CAT(FastDelegate, BOOST_PP_ITERATION())<BOOST_PP_ENUM_PARAMS(NUM_EVENT_ARGS, T)> DelegateType;
	typedef detail::Node<DelegateType> NodeType;

public:
	Event() : m_listeners(0) { }
	~Event()
	{
		while(m_listeners != 0)
		{
			NodeType* oldListener = m_listeners;
			m_listeners = m_listeners->next;
			if(oldListener->refCount == 0)
			{
				delete oldListener;
			}
			else
			{
				oldListener->refCount = -oldListener->refCount;
			}
		}
	}

	template<typename ClassType, typename CallbackType>
	Connection Register(ClassType &object, CallbackType const& callback)
	{
		m_listeners = new NodeType(fastdelegate::MakeDelegate(&object, callback), m_listeners);
		return Connection(m_listeners);
	}

	void ERROR_OnlyAutoTrackedObjectsCanUseAutoRegister(AutoTracked &) { }

	template<typename ClassType, typename CallbackType>
	void AutoRegister(ClassType &object, CallbackType const& callback)
	{
		ERROR_OnlyAutoTrackedObjectsCanUseAutoRegister(object);

		static_cast<AutoTracked &>(object).Add(Register(object, callback));
	}

	void Invoke(BOOST_PP_ENUM_BINARY_PARAMS(NUM_EVENT_ARGS, T, arg))
	{
		// delete unreferenced listeners at head
		NodeType* listener = m_listeners;
		while(listener != 0 && listener->refCount == 0)
		{
			NodeType* oldListener = listener;
			listener = listener->next;
			delete oldListener;
		}
		m_listeners = listener;

		// iterate over remaining listeners, deleting unused ones
		NodeType* prevListener = 0;
		while(listener != 0)
		{
			if(listener->refCount != 0)
			{
				Connection c(listener);
				listener->data(BOOST_PP_ENUM_PARAMS(NUM_EVENT_ARGS, arg));
				if(!c.Active())
				{
					return;
				}
				prevListener = listener;
				listener = listener->next;
			}
			else
			{
				NodeType* oldListener = listener;
				listener = listener->next;
				delete oldListener;
				prevListener->next = listener;
			}
		}
	}

private:
	NodeType* m_listeners;
};