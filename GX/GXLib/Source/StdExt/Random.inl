namespace GX
{
	template <class Engine>
	typename Engine::result_type random(Engine& engine)
	{
		return engine();
	}

	template <class T, class Engine>
	T random(T min, T max, Engine& engine)
	{
		return (min + (engine() % (max - min + 1)));
	}
}