set -e
set -x
echo Testing
if [ -z BOOST_BJAM_LOCATION ]
then
  BOOST_BJAM_LOCATION=bjam
fi
BOOST_SANDBOX_ROOT=`pwd`
BOOST_ROOT=`pwd`
for f in libs/extension/examples libs/reflection/examples libs/reflection/test libs/extension/test 
do
  cd $BOOST_ROOT/$f
  echo `pwd`
  BOOST_SANDBOX_ROOT=$BOOST_SANDBOX_ROOT BOOST_ROOT=$BOOST_ROOT $BOOST_BJAM_LOCATION $BOOST_BJAM_OPTIONS
done