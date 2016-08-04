#pragma once

namespace PathPlan{
    class PathMode;
};

namespace PathPlan{
    class Planner{
        private:
            Planner();
			~Planner();
            static Planner *main_instance;
            PathMode *curPlanner = 0;
            PathMode *nextPlanner = 0;
            int count = 0;
            void swapPlanner();

        public:
			static Planner *getInstance();
            void setNextPlanner(PathMode *newPlanner);

            void update();

            /*
             * EHandler signal rerouting.
             */
            void finishedTurnAround();
            void finishedIntersect();
            void finishedPickUp();
            void finishedDropOff();
            void reverseIntersect();
    }; 
};
